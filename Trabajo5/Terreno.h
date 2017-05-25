#ifndef TERRENO_H_INCLUDED
#define TERRENO_H_INCLUDED
using namespace std;
static int slices = 16;
static int stacks = 16;

int str_to_float(string s)
{

    string str = s;
    istringstream buffer(str);
    float value;
    buffer >> value;
    return value;
}
typedef struct // Definicion de un punto del terreo
{
    GLfloat s, t; // Coordenadas de texturas
    GLfloat nx, ny, nz; // Coordenadas de la normal
    GLfloat x, hauteur, z; // posición del vértice
} PuntoTerreno;

class Terreno
{
    public :
    Terreno(){}
    ~Terreno(){}
    bool load(char *filename) ; // carga de un archivo de modelo digital de terreno
    void display(); // Visualizacion del terreno
    void computeNormals(); // calcula las normales de cada vertice
    private:
    int nb_pt_x, nb_pt_z; // quantidad de punto en X y Z
    float dist_x, dist_z; // distancia entre dos puntos segun X y Z
    PuntoTerreno* lista_puntos; // Tabla que contiene los puntos  del terreno
    GLuint *lista_indices ; // Tabla que contiene los indicess
};
bool Terreno::load(char * filename)
{
    nb_pt_x = 0;
    nb_pt_z = 0;
    fstream fichero;
    string aux,aux2;
    PuntoTerreno* vec = new PuntoTerreno[101*101];
    lista_puntos = vec;
    int contador = 0;
    int contador2 = 0;
    fichero.open(filename, ios::in);
    if (fichero.is_open())
    {
        while (! fichero.eof() )
        {
            getline (fichero,aux);
            contador = 0;
            for (int i = 0; i<(int)aux.size() ; i++)
            {
                if (int(aux[i]) != 32)
                {
                    aux2.push_back(aux[i]);
                }
                else
                {
                    vec->x = contador*50;
                    vec->hauteur = str_to_float(aux2);
                    vec->z = contador2*50;
                    vec++;
                    nb_pt_x++;
                    contador++;
                    aux2.clear();
                }
            }
            contador2++;
        }
    }
    else
    {
        return 0;
        cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
    }
    fichero.close();
    nb_pt_z = contador;
    nb_pt_x = nb_pt_x/nb_pt_z;
    GLuint * auxiliar = new GLuint[100*100*6];
    lista_indices = auxiliar;
    for (int i = 0; i<nb_pt_z - 1; i++)
    {
        for (int j = 0; j<nb_pt_x - 1; j++)
        {
            *auxiliar = i*nb_pt_z+j;
            auxiliar++;
            *auxiliar = (i+1) * nb_pt_z+j;
            auxiliar++;
            *auxiliar=(i+1)*nb_pt_z+(j+1);
            auxiliar++;
            *auxiliar=i*nb_pt_z+j;
            auxiliar++;
            *auxiliar=(i+1)*nb_pt_z+(j+1);
            auxiliar++;
            *auxiliar=i*nb_pt_z+(j+1);
            auxiliar++;
        }
    }
    return 1;
}

void Terreno::display()
{
    glColor3f(1.0f,0.0f,0.0f);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(PuntoTerreno),&lista_puntos[0].s);
    glDrawElements(GL_TRIANGLES, 100*100*6, GL_UNSIGNED_INT,(void*)lista_indices);
}



#endif // TERRENO_H_INCLUDED
