
class Singleton {
   public:
    static Singleton& GetInstance() {
        static Singleton instance;
        return instance;
    }

   protected:
    Singleton() {}

   public:
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;
};

