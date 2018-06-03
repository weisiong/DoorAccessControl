#ifndef HEADER_DOOR_CONTROL
#define HEADER_DOOR_CONTROL
   
class DOOR_CONTROL{
    public:
      void setup( void );
      void Open(int closeAfterSecs);
      void Close();
};
   
#endif
