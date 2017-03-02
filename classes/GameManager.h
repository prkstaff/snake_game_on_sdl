#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_
class GameManager{
    private:
        static GameManager* manager_;
        static int SCREEN_WIDTH;
        ~GameManager();
    public:
        static GameManager* instance();
        int get_SCREEN_WIDTH();
        void set_SCREEN_WIDTH(int);
};
#endif /* ifndef _GAMEMANAGER_
class GameManager{
    private:
        static GameManager* manager_;
    public:
        static GameManager* instance();
} */
