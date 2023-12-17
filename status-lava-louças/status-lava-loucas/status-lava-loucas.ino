#include <SPI.h>
#include <SD.h>
#include <Pushbutton.h>

const int sdModulePin = 10;
Pushbutton changeButton(2);

String fileName = "datalog.txt";

void setup() {
  Serial.begin(9600);

  if (!SD.begin(sdModulePin)) {
    Serial.println("initialization failed!");
    while (1);
  }
  verifyDatalogExists();
  readDatalog();
  delay(10);
}

void loop() {
  if(changeButton.getSingleDebouncedPress()){
    change();
    delay(100);
    readDatalog();
  }
}

void verifyDatalogExists() {
  File root = SD.open("/");
  bool datalogExists = false;
  while (true) {
    File entry =  root.openNextFile();
    if (! entry) { // no more files
      break;
    }
    
    String entryName(entry.name());
    if (!entry.isDirectory() && entryName.equalsIgnoreCase(fileName)) {
      datalogExists = true;      
    }
    entry.close();
  }
  root.close();
  if(!datalogExists){
    Serial.print("Arquivo ");
    Serial.print(fileName);
    Serial.println(" não encontrado!");
    createDatalog();
  }
}

void createDatalog(){
  Serial.println("Criando arquivo inicial");
  File datalog = getDatalog(FILE_WRITE);
  datalog.println("numberOfWashes:0;isClean:0");
  datalog.close();
  Serial.println("Arquivo datalog criado.");
}

void readDatalog(){
  File datalog = getDatalog(O_READ);
  Serial.println("==== Conteudo do datalog ====");
  while (datalog.available()) {
    Serial.write(datalog.read());
  }
  datalog.close();
  Serial.println("==== Conteudo do datalog finalizado ====");
  delay(10);
}

int getNumberOfWashes(){
  File datalog = getDatalog(O_READ);
  String values = datalog.readString();
  int numberOfWashes = values.charAt(15) - 48;
  datalog.close();
  return numberOfWashes;
}

int getIsClean(){
  File datalog = getDatalog(O_READ);
  String values = datalog.readString();
  int isClean = values.charAt(25) - 48;
  datalog.close();
  return isClean;
}

File getDatalog(uint8_t mode){
  File datalog = SD.open(fileName, mode);
  if (datalog) {
    return datalog;
  } else {
    Serial.print("error opening ");
    Serial.println(fileName);
  }
}

void change(){
  Serial.println("Alterando estado...");
  File datalog = getDatalog(O_RDWR);
  datalog.seek(0);
  int nWashes = getNumberOfWashes();
  int isClean = getIsClean();

  if(isClean == 0){
    isClean == 1;
  } else {
    isClean == 0;
  }
  datalog.print("numberOfWashes:");
  datalog.print(++nWashes);
  datalog.print(";isClean:");
  datalog.println(!isClean);

  datalog.close();
  Serial.println("Estado alterado");
}