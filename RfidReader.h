#ifndef HEADER_RFID_READER
#define HEADER_RFID_READER
   
class RFID_READER{
    public:
      void setup( void );
      void loop( void );
      bool ReadTag(String &tagId);
};
   
#endif
