

using namespace std;

#define MAX_TOUCHES 7

typedef struct TOUCH TOUCH;
struct TOUCH {
//class TOUCH {
public:
   int id;
   int x;
   int y;
};

static void draw_touches(int num, TOUCH touches[]);
static int find_index(int id, int num, TOUCH touches[]);
int touch_main();