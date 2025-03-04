#include "lib/table.h"
#include "btree/node.h"
#include "lib/row.h"
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *get_page(Pager *pager, uint32_t page_num) {
  if (page_num > TABLE_MAX_PAGES) {
    printf("page `%d` is out of bounds (max `%d`).", page_num, TABLE_MAX_PAGES);
    exit(EXIT_FAILURE);
  }

  if (pager->pages[page_num] == NULL) {
    void *page = malloc(PAGE_SIZE);
    uint32_t num_pages = pager->file_length / PAGE_SIZE;

    if (page_num <= num_pages) {
      lseek(pager->fd, page_num * PAGE_SIZE, SEEK_SET);
      ssize_t bytes_read = read(pager->fd, page, PAGE_SIZE);
      if (bytes_read == -1) {
        printf("faild to read file with descriptor: `%d`.\n", pager->fd);
        exit(EXIT_FAILURE);
      }
    }

    pager->pages[page_num] = page;

    if (page_num >= pager->num_pages) {
      pager->num_pages = page_num + 1;
    }
  }

  return pager->pages[page_num];
}

Pager *pager_open(const char *filename) {
  int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

  if (fd == -1) {
    printf("unable to open db file.\n");
    exit(EXIT_FAILURE);
  }

  off_t file_length = lseek(fd, 0, SEEK_END);

  Pager *pager = malloc(sizeof(Pager));
  pager->fd = fd;
  pager->file_length = file_length;
  pager->num_pages = file_length / PAGE_SIZE;

  if (file_length % PAGE_SIZE != 0) {
    printf("corrupt db file.\n");
    exit(EXIT_FAILURE);
  }

  for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
    pager->pages[i] = NULL;
  }

  return pager;
}

Table *db_open(const char *filename) {
  Pager *pager = pager_open(filename);

  Table *table = malloc(sizeof(Table));
  table->pager = pager;
  table->root_page_num = 0;

  if (pager->num_pages == 0) {
    // new database file.
    void *root_node = get_page(pager, 0);
    initialize_leaf_node(root_node);
  }

  return table;
}

void pager_flush(Pager *pager, uint32_t page_num) {
  if (pager->pages[page_num] == NULL) {
    printf("attempted to flush a null page.\n");
    exit(EXIT_FAILURE);
  }

  off_t offset = lseek(pager->fd, page_num * PAGE_SIZE, SEEK_SET);
  if (offset == -1) {
    printf("failed to flush page: %d.\n", errno);
    exit(EXIT_FAILURE);
  }

  ssize_t bytes_written = write(pager->fd, pager->pages[page_num], PAGE_SIZE);
  if (bytes_written == -1) {
    printf("failed to flush page: %d.\n", errno);
    exit(EXIT_FAILURE);
  }
}

void db_close(Table *table) {
  Pager *pager = table->pager;

  for (uint32_t i = 0; i < pager->num_pages; i++) {
    if (pager->pages[i] == NULL) {
      // page is not dirty, i. e. was not written to or read from
      continue;
    }
    page_flush(pager, i);
    free(pager->pages[i]);
    pager->pages[i] = NULL;
  }

  int result = close(pager->fd);
  if (result == -1) {
    printf("failed to close db file.\n");
    exit(EXIT_FAILURE);
  }

  free(pager);
  free(table);
}