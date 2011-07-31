void print_bauds(void);

#define BAUD_MSG_LEN 210
#define NUM_BAUDS 14
#define DEFAULT_BAUD_INDEX 8

static unsigned int ubrgs[] = {2499,624,311,155,77,38,77,12,25,12,5,2,1,0};

static unsigned char brghs[] = {0,0,0,0,0,0,1,0,1,1,1,1,1,1};

