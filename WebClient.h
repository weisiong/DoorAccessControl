#ifndef HEADER_WEB_CLIENT
#define HEADER_WEB_CLIENT
   
class WEB_CLIENT{
    public:
      void setup( void );
      int webget(const String& URLPath, String& resBody, int& resCode);
};
   
#endif
