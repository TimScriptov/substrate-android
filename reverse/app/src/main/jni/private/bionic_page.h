#ifndef _BIONIC_PAGE_H_
#define _BIONIC_PAGE_H_
 
// Get PAGE_SIZE and PAGE_MASK.
#include <sys/user.h>
 
// Returns the address of the page containing address 'x'.
#define PAGE_START(x) ((x) & PAGE_MASK)
 
// Returns the offset of address 'x' in its page.
#define PAGE_OFFSET(x) ((x) & ~PAGE_MASK)
 
// Returns the address of the next page after address 'x', unless 'x' is
// itself at the start of a page.
#define PAGE_END(x) PAGE_START((x) + (PAGE_SIZE-1))
 
#endif // _BIONIC_PAGE_H_
 
