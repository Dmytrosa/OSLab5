#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <X11/XKBlib.h>

using namespace std;
int main()
{
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    int fd = open(dev, O_RDONLY);
    if (fd == -1)
    {
        cerr << "Cannot open " << dev << endl;
        return 1;
    }
    Display *display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        cerr << "Cannot open X11 display." << endl;
        return 1;
    }
    cout << "I am copycat and I am going to copy everything you do ( •̀ᴗ•́ )و ̑̑" << endl;
    struct input_event ev;
    while (true)
    {
        read(fd, &ev, sizeof(ev));
        if (ev.type == EV_KEY && ev.value == 1)
        {
            cout << "Process ID: " << getpid() << endl;
            KeySym keySym = XkbKeycodeToKeysym(display, ev.code, 0, 0);
            char symbol = static_cast<char>(keySym);
            cout << "Have you pressed " << symbol << "? ;)" << endl;
        }
    }
    close(fd);
    return 0;
}
