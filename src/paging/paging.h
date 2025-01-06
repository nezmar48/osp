#ifndef PAGING_H
#define PAGING_H

// Function to initialize a page directory
// @param page_directory: Pointer to the page directory to be initialized
// @return: Pointer to the initialized page directory
unsigned long* init_page_directory(unsigned long* page_directory);

#endif // PAGING_H
