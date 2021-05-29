#include <kernel/arch/i386/paging.h>

#include <kernel/thread.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>

extern "C" void flush_tlb();

extern "C" uint32_t *page_map;

bool used_alloc_id(uint32_t x) {
	for(uint32_t i = 0; i < 0x100000; i++) if(x == page_map[i]) return true;
	return false;
}

uint32_t get_alloc_id() {
	for(uint32_t i = 2; i < 0x100000; i++) if(!used_alloc_id(i)) return i;
	return -1;
}

void *get_physaddr(void *virtualaddr) {
	uint32_t pdindex = (uint32_t)virtualaddr >> 22;
	uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03FF;

	uint32_t *pd = (uint32_t*)0xFFFFF000;
	if(pd[pdindex] == 0) {
		// throw -1; no exception handling yet
		printf("get_physaddr: error: virtual address [%08x] not mapped\n",
			(uint32_t)virtualaddr
		);
		return nullptr;
	}

	uint32_t *pt = ((uint32_t*)0xFFC00000) + (0x400 * pdindex);
	if(pt[ptindex] == 0) {
		// throw -1; no exception handling yet
		printf("get_physaddr: error: virtual address [%08x] not mapped\n",
			(uint32_t)virtualaddr
		);
		return nullptr;
	}

	return (void*)((pt[ptindex] & ~0xFFF) + ((uint32_t)virtualaddr & 0xFFF));
}

void map_page(void *physaddr, void *virtualaddr, uint32_t flags) {
	uint32_t pdindex = (uint32_t)virtualaddr >> 22;
	uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03FF;

	uint32_t pmindex = (uint32_t)physaddr >> 12;

	uint32_t *pd = (uint32_t*)0xFFFFF000;
	if(pd[pdindex] == 0) {
		pd[pdindex] = (0x800000 + 0x1000 * pdindex) | 0x03;
	}

	uint32_t *pt = ((uint32_t*)0xFFC00000) + (0x400 * pdindex);

	if(page_map[pmindex] != 0) {
		// throw -1; no exception handling yet
		printf("map_page: error: physical memory [%08x - %08x] already allocated\n",
			pmindex * 0x1000,
			pmindex * 0x1000 + 0xFFF
		);
		return;
	}
	
	if(pt[ptindex] != 0) {
		// throw -1; no exception handling yet
		printf("map_page: error: virtual memory [%08x - %08x] already mapped to [%08x - %08x]\n",
			pdindex * 0x400000 + ptindex * 0x1000,
			pdindex * 0x400000 + ptindex * 0x1000 + 0xFFF,
			pmindex * 0x1000,
			pmindex * 0x1000 + 0xFFF
		);
		return;
	}

	pt[ptindex] = ((uint32_t)physaddr & 0xFFFFF000) | (flags & 0xFFF) | PAGE_PRESENT;
}

void unmap_page(void *virtualaddr) {
	uint32_t pdindex = (uint32_t)virtualaddr >> 22;
	uint32_t ptindex = (uint32_t)virtualaddr >> 12 & 0x03FF;

	uint32_t *pd = (uint32_t*)0xFFFFF000;
	if(pd[pdindex] == 0) {
		// throw -1; no exception handling yet
		printf("unmap_page: error: double free()\n");
		return;
	}

	uint32_t *pt = ((uint32_t*)0xFFC00000) + (0x400 * pdindex);

	if(pt[ptindex] == 0) {
		// throw -1; no exception handling yet
		printf("unmap_page: error: double free()\n");
		return;
	}

	pt[ptindex] = 0;
	for(uint32_t i = 0; i < 0x400; i++) {
		if(pt[i] != 0) return;
	}
	pd[pdindex] = 0;
}

extern "C" {
	void *_malloc(uint32_t size, uint32_t flags = PAGE_READWRITE) {
		uint32_t *pd = (uint32_t*)0xFFFFF000;

		bool has_address = false;
		void *return_address = 0;
		uint32_t available_size = 0;

		for(uint32_t i = 0; i < 0x400; i++) {

			if(!(pd[i] & PAGE_PRESENT)) {
				available_size += 0x400000;
				if(!has_address) {
					return_address = (void*)(i * 0x400000);
					has_address = true;
				}
				if(available_size >= size) break;
				continue;
			}

			uint32_t *pt = (uint32_t*)(0xFFC00000 + (0x1000 * i));

			for(uint32_t j = 0; j < 0x400; j++) {
				if(pt[j] == 0) {
					available_size += 0x1000;
					if(!has_address) {
						return_address = (void*)(i * 0x400000 + j * 0x1000);
						has_address = true;
					}
					if(available_size >= size) break;
					continue;
				}
				return_address = 0;
				has_address = false;
				available_size = 0;
			}

			if(available_size >= size) break;

		}

		if(!has_address) {
			printf("_malloc: error: couldn't find any available virtual memory.\n");
			// throw std::bad_alloc("malloc: error: couldn't find any available virtual memory.");
			return nullptr;
		}

		uint32_t allocated = 0;
		uint32_t alloc_id = get_alloc_id();

		for(uint32_t x = 0; x < size / 0x1000 + ((size % 0x1000) ? 1 : 0); x++) {
			for(uint32_t i = 0; i < 0xFFFFF; i++) {
				if(page_map[i] != 0) continue;
				map_page((void*)(i * 0x1000), return_address + allocated * 0x1000, flags);
				page_map[i] = alloc_id;
				allocated++;
				if(allocated == size / 0x1000 + ((size % 0x1000) ? 1 : 0)) {
					flush_tlb();
					return return_address;
				}
			}
		}

		printf("_malloc: error: out of memory.\n");
		// throw std::bad_alloc("malloc: error: out of memory.");
		return nullptr;
	}

	void _free(void *ptr) {
		void *physaddr = get_physaddr(ptr);
		// do something to check physaddr actually exists once exceptions are implemented

		uint32_t id = ((uint32_t)physaddr & ~0xFFF) >> 12;
		uint32_t n = 1;

		for(uint32_t i = 0; i < 0xFFFFF; i++) if(page_map[i] == page_map[id] && i != id) {
			unmap_page(ptr + (0x1000 * n));
			n++;
			page_map[i] = 0; // Unmap from kernel table
		}
		unmap_page(ptr);
		page_map[id] = 0;
		flush_tlb();
	}

	void *_realloc(void *ptr, uint32_t size, uint32_t flags = PAGE_READWRITE) {
		void *physaddr = get_physaddr(ptr);
		// do something to check physaddr actually exists once exceptions are implemented

		uint32_t id = ((uint32_t)physaddr & ~0xFFF) >> 12;

		uint32_t old_size = 0;
		for(uint32_t i = 0; i < 0xFFFFF; i++) if(page_map[i] == page_map[id]) {
			old_size += 0x1000;
		}

		if(size <= old_size - 0x1000) {			// Remove pages
			uint32_t d_size = old_size - size;
			for(uint32_t i = 0; i < d_size / 0x1000; i++) {
				void *virtualaddr = ptr + old_size - (i + 1) * 0x1000;
				physaddr = get_physaddr(virtualaddr);
				// do something to check physaddr actually exists once exceptions are implemented
				unmap_page(virtualaddr);
				page_map[((uint32_t)physaddr & ~0xFFF) >> 12] = 0;
			}
			return ptr;
		} else if(size > old_size) {			// Add pages
			uint32_t d_size = size - old_size;
			uint32_t available_size = 0;

			for(uint32_t i = ((uint32_t) + old_size) >> 22; i < 0x400; i++) {
				uint32_t *pd = (uint32_t*)0xFFFFF000;
				if(pd[i] == 0) {
					available_size += 0x400000;
					if(available_size >= d_size) break;
					continue;
				}

				uint32_t *pt = ((uint32_t*)0xFFC00000 + (0x1000 * i));

				for(uint32_t j = 0; j < 0x400; j++) {
					if(pt[j] == 0) {
						available_size += 0x1000;
						if(available_size >= d_size) break;
						continue;
					}
				}

				// Need to move the virtual address... too much hassle, just free and reallocate (ik, less efficient, this is just temporary for now)
				void *ret = _malloc(size);
				if(ret == nullptr) return ret;
				memcpy(ret, ptr, old_size);
				_free(ptr);
				return ret;

			}

			uint32_t allocated = old_size / 0x1000;

			for(uint32_t x = 0; x < d_size / 0x1000 + ((d_size % 0x1000) ? 1 : 0); x++) {
				for(uint32_t i = 0; i < 0xFFFFF; i++) {
					if(page_map[i] != 0) continue;
					map_page((void*)(i * 0x1000), ptr + allocated * 0x1000, flags);
					page_map[i] = page_map[id];
					allocated++;
					if(allocated == size / 0x1000 + ((d_size % 0x1000) ? 1 : 0)) {
						return ptr;
					}
				}
			}

			printf("_realloc: error: out of memory. allocated: %i out of %i\n", allocated, size / 0x1000 + ((size % 0x1000) ? 1 : 0));
			// throw std::bad_alloc("realloc: error: out of memory.");
			return nullptr;

		} else return ptr;						// Nothing changed
	}
}
