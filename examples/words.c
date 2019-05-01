// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

#include <m_trie.h>

int
main(void)
{
  char* text;
  struct stat st;
  int fd;
  struct m_trie tr;
  int64_t i;
  int64_t k;
  struct timeval start;
  struct timeval end;

  // Open the dictionary for reading.
  fd = open("/usr/share/dict/words", O_RDONLY);
  if (fd < 0) {
    perror("open");
    return EXIT_FAILURE;
  }

  // Obtain the size of the file.
  if (fstat(fd, &st) == -1) {
    perror("fstat");
    return EXIT_FAILURE;
  }

  // Load the file's content into the memory.
  text = mmap(NULL, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (text == MAP_FAILED) {
    perror("mmap");
    return EXIT_FAILURE;
  }

  m_trie_init(&tr, m_trie_hash_alphabet, 0);
  i = 0;

  // Scan through all words and insert them into the trie.
  gettimeofday(&start, NULL);
  while (i < st.st_size) {
    // Find the end of the current word.
    for (k = 0; k < st.st_size; k++) {
      if (text[i + k] == '\n') {
        break;
      }
    }

    m_trie_insert(&tr, (uint8_t*)&text[i], (uint32_t)k, NULL);
    i += k + 1;
  }
  gettimeofday(&end, NULL);

  // Compute and print the time taken to build the data structure.
  printf("Time taken: %ldus\n", ((end.tv_sec - start.tv_sec) * 1000000L) +
                                (end.tv_usec - start.tv_usec));

  munmap(text, (size_t)st.st_size);
  close(fd);

  return EXIT_SUCCESS;
}
