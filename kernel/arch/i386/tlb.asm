global flush_tlb
flush_tlb:
	push eax
	mov eax,cr3
	mov cr3,eax
	pop eax
	ret
