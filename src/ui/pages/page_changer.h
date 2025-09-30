#ifndef PAGE_CHANGER_H
#define PAGE_CHANGER_H

void change_page(void (*delete_old_page) (void), void (*init_new_page) (void));

#endif
