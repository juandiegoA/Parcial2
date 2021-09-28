#include <iostream>
#include <QImage>
#include <cmath>
#include <fstream>
using namespace std;
class imagen{
private:
    string ruta;
    int alto;
    int ancho;
    string rutaTXT;
public:
    imagen(string,string);
    void Muestreo();
};
imagen::imagen(string _rutaImagen,string _rutaTXT){
    ruta=_rutaImagen;
    rutaTXT=_rutaTXT;
    QImage ima(ruta.c_str());
    alto=ima.height();
    ancho=ima.width();
};
void imagen::Muestreo(){
    ofstream file;
    file.open(rutaTXT);
    QImage ima(ruta.c_str());
    int contador=0;
    double muestraX=ancho*0.125;
    double muestraY=alto*0.125;
    if(muestraX>=1||muestraY>=1){
        for(int i=(muestraY/2);i<alto;i+=(muestraY)){//alto
            for(int j=muestraX/2;j<ancho;j+=muestraX){//ancho
                file << to_string(ima.pixelColor(j,i).red())<<",";
                file << to_string(ima.pixelColor(j,i).green())<<",";
                file << to_string(ima.pixelColor(j,i).blue())<<",";
                contador++;
            }

        }
    }else{
        //sobremuestreo
        double avanceX=0;
        double avanceY=0;
        for(int i=0;i<8;i++){ //alto
            for(int j=0;j<8;j++){//ancho
                file << to_string(ima.pixelColor(floor(avanceX),floor(avanceY)).red())<<",";
                file << to_string(ima.pixelColor(floor(avanceX),floor(avanceY)).green())<<",";
                file << to_string(ima.pixelColor(floor(avanceX),floor(avanceY)).blue())<<",";
                contador++;
                avanceX=muestraX+avanceX;
            }
            avanceX=0;
            avanceY=muestraY+avanceY;
        }
    }
    cout<<ancho<<" x "<<alto<<"  muestreo culminado con EXITO"<<contador<<endl;
    file.close();
};
int main()
{
    string ruta="../pruebas1/flags/jap.jpg";
    string rutaTXT="../pruebas1/archivo.txt";
    QImage im(ruta.c_str());
    imagen bandera(ruta,rutaTXT);
    bandera.Muestreo();
    return 0;
}
