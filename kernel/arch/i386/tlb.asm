global flush_tlb
flush_tlb:
	push eax
	mov cr3,eax
	mov eax,cr3
	pop eax
	ret
