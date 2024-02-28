/*
 * Loader Implementation
 *
 * 2022, Operating Systems
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/mman.h>
#include "macro.h"
#include "exec_parser.h"

static int fd;
static so_exec_t *exec;
static char *p;
static void *q;
static char* cale; 
static int **a;
static int page_size;

static void segv_handler(int signum, siginfo_t *info, void *context)
{
	fd = open(cale,O_RDONLY);
	int page, segm_vaddr, file_size, mem_size, offset_mapping;
	int index_seg = -1;
	void *addr_mapping;
	char *addr_pagefault;

	//se cauta segmentul 
	addr_pagefault = (char *) info->si_addr;
	for (int i = 0; i < exec->segments_no; i++) {
		char *vaddr = (char *)exec->segments[i].vaddr;
		if (vaddr <= addr_pagefault && addr_pagefault <= vaddr + exec->segments[i].mem_size)
			index_seg = i; }

	if(index_seg != -1) {
	//se identifica pagina 
	segm_vaddr = exec->segments[index_seg].vaddr;
	page = ((int) addr_pagefault - segm_vaddr) / page_size;
	//pentru claritate, campurile structurii des utilizate se retin in variabile
	mem_size = exec->segments[index_seg].mem_size;
	file_size = exec->segments[index_seg].file_size;
	offset_mapping = exec->segments[index_seg].offset + page * page_size;
	addr_mapping = (void *)  ((page * page_size) + segm_vaddr);
	} else {
		for(int i = 0; i < exec->segments_no; i++)
			free(a[i]);
		free(a);
		close(fd);
		exit(139); }

	if(a[index_seg][page] == 0) {
		int beginning_of_page_size = page * page_size, end_of_page_size = (page + 1) * page_size;
		//cele 3 cazuri in care se poate afla pagina ce trebuie mapata
		if (beginning_of_page_size < file_size && file_size < end_of_page_size) { 
			p = mmap(addr_mapping, page_size, exec->segments[index_seg].perm, MAP_FIXED | MAP_PRIVATE, fd, offset_mapping);
			DIE(p == (void*)-1, "mmap error");
			a[index_seg][page] = 1;
			if (end_of_page_size < mem_size)
				q = memset((void *)segm_vaddr + file_size, 0, end_of_page_size - file_size);
			else
				q = memset((void *)segm_vaddr + file_size, 0, mem_size - file_size);
			DIE(q != (void *)segm_vaddr + file_size, "memset error");

		} else if (beginning_of_page_size < file_size  && end_of_page_size <= file_size) { 
			p = mmap(addr_mapping, page_size, exec->segments[index_seg].perm, MAP_FIXED | MAP_PRIVATE, fd, offset_mapping);
			DIE(p == (void*)-1,"mmap error");
			a[index_seg][page] = 1; 
			} else { 
			p = mmap(addr_mapping, page_size, exec->segments[index_seg].perm, MAP_ANONYMOUS | MAP_FIXED | MAP_PRIVATE, -1, 0);
			DIE(p == (void*)-1,"mmap error");
			a[index_seg][page] = 1; }
	} else {
		for(int i = 0; i < exec->segments_no; i++)
			free(a[i]);
		free(a);
		close(fd);
		exit(139); }
}

int so_init_loader(void)
{
	int rc;
	struct sigaction sa;
	page_size = getpagesize();
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = segv_handler;
	sa.sa_flags = SA_SIGINFO;
	rc = sigaction(SIGSEGV, &sa, NULL);
	if (rc < 0) {
		perror("sigaction");
		return -1;
	}
	return 0;
}

int so_execute(char *path, char *argv[])
{
	cale = path;
	exec = so_parse_exec(path);
	// a este o matrice ce tine evidenta paginilor mapate
	a = malloc(exec->segments_no*sizeof(int*));
	for(int i = 0; i < exec->segments_no; i++) {
		int aux = exec->segments[i].mem_size/page_size + 1;
		a[i] = calloc(aux, aux*sizeof(int)); }
	if (!exec)
		return -1;
	so_start_exec(exec, argv);
	return -1;
}
