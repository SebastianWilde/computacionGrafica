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


void cNormal (GLfloat  normal [3],GLfloat vector1 [3], GLfloat vector2 [3])
{
    GLfloat distancia = 0;
    normal[0] = vector1[1]*vector2[2] - vector1[2]*vector2[1];
    normal[1] = (vector1[0]*vector2[2] - vector1[2]*vector2[0])*-1;
    normal[2] = vector1[0]*vector2[1] - vector1[1]*vector2[0];
    for (int i=0;i<3;i++)
        distancia += pow(normal[i],2);
    distancia = sqrt(distancia);
    for (int i=0;i<3;i++)
        normal[i] /= distancia;
    return;
}

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
    float cont_v = 1.0f/101.0f;
    float cont_t = 0;
    float cont_s = 0;
    fichero.open(filename, ios::in);
    if (fichero.is_open())
    {
        while (! fichero.eof() )
        {
            getline (fichero,aux);
            contador = 0;
            cont_s = 0;
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
                    vec->s = cont_s;
                    vec->t = cont_t;
                    cont_s += cont_v;
                    vec++;
                    nb_pt_x++;
                    contador++;
                    aux2.clear();
                }
            }
            contador2++;
            cont_t+=cont_v;
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

void Terreno::computeNormals()
{
    GLfloat vector1 [3];
    GLfloat vector2 [3];
    GLfloat normal[3];
    int contador;
    for(int i=0;i<nb_pt_z;i++)
    {
        for (int j=0;j<nb_pt_x;j++)
        {
            int pos = i*nb_pt_z+j;
            contador = 0;
            if (j+1<nb_pt_x && i+1<nb_pt_z)
            {
                vector1[0] = lista_puntos[pos+1].x - lista_puntos[pos].x;
                vector1[1] = lista_puntos[pos+1].hauteur - lista_puntos[pos].hauteur;
                vector1[2] = lista_puntos[pos+1].z - lista_puntos[pos].z;

                vector2[0] = lista_puntos[pos+nb_pt_x+1].x - lista_puntos[pos].x;
                vector2[1] = lista_puntos[pos+nb_pt_x+1].hauteur - lista_puntos[pos].hauteur;
                vector2[2] = lista_puntos[pos+nb_pt_x+1].z - lista_puntos[pos].z;

                cNormal(normal,vector1,vector2);
                lista_puntos[pos].nx=normal[0];
                lista_puntos[pos].ny=normal[1];
                lista_puntos[pos].nz=normal[2];
                contador++;

                vector1[0] = lista_puntos[pos+nb_pt_x].x - lista_puntos[pos].x;
                vector1[1] = lista_puntos[pos+nb_pt_x].hauteur - lista_puntos[pos].hauteur;
                vector1[2] = lista_puntos[pos+nb_pt_x].z - lista_puntos[pos].z;

                cNormal(normal,vector1,vector2);
                contador++;
            }

            if (j-1>=0 && i+1<nb_pt_z)
            {
                vector1[0] = lista_puntos[pos-1].x - lista_puntos[pos].x;
                vector1[1] = lista_puntos[pos-1].hauteur - lista_puntos[pos].hauteur;
                vector1[2] = lista_puntos[pos-1].z - lista_puntos[pos].z;

                vector2[0] = lista_puntos[pos+nb_pt_x].x - lista_puntos[pos].x;
                vector2[1] = lista_puntos[pos+nb_pt_x].hauteur - lista_puntos[pos].hauteur;
                vector2[2] = lista_puntos[pos+nb_pt_x].z - lista_puntos[pos].z;
                cNormal(normal,vector1,vector2);
                lista_puntos[pos].nx=normal[0];
                lista_puntos[pos].ny=normal[1];
                lista_puntos[pos].nz=normal[2];
                contador++;
            }

            if (j-1>=0 && i-1>=0)
            {
                vector1[0] = lista_puntos[pos-1].x - lista_puntos[pos].x;
                vector1[1] = lista_puntos[pos-1].hauteur - lista_puntos[pos].hauteur;
                vector1[2] = lista_puntos[pos-1].z - lista_puntos[pos].z;

                vector2[0] = lista_puntos[pos+nb_pt_x-1].x - lista_puntos[pos].x;
                vector2[1] = lista_puntos[pos+nb_pt_x-1].hauteur - lista_puntos[pos].hauteur;
                vector2[2] = lista_puntos[pos+nb_pt_x-1].z - lista_puntos[pos].z;

                cNormal(normal,vector1,vector2);
                lista_puntos[pos].nx=normal[0];
                lista_puntos[pos].ny=normal[1];
                lista_puntos[pos].nz=normal[2];
                contador++;

                vector1[0] = lista_puntos[pos-nb_pt_x].x - lista_puntos[pos].x;
                vector1[1] = lista_puntos[pos-nb_pt_x].hauteur - lista_puntos[pos].hauteur;
                vector1[2] = lista_puntos[pos-nb_pt_x].z - lista_puntos[pos].z;

                cNormal(normal,vector1,vector2);
                contador++;
            }

            if (j+1<nb_pt_x && i-1>=0)
            {
                vector1[0] = lista_puntos[pos+1].x - lista_puntos[pos].x;
                vector1[1] = lista_puntos[pos+1].hauteur - lista_puntos[pos].hauteur;
                vector1[2] = lista_puntos[pos+1].z - lista_puntos[pos].z;

                vector2[0] = lista_puntos[pos-nb_pt_x].x - lista_puntos[pos].x;
                vector2[1] = lista_puntos[pos-nb_pt_x].hauteur - lista_puntos[pos].hauteur;
                vector2[2] = lista_puntos[pos-nb_pt_x].z - lista_puntos[pos].z;
                cNormal(normal,vector1,vector2);
                lista_puntos[pos].nx=normal[0];
                lista_puntos[pos].ny=normal[1];
                lista_puntos[pos].nz=normal[2];
                contador++;
            }
            lista_puntos[pos].nx/=contador;
            lista_puntos[pos].ny/=contador;
            lista_puntos[pos].nz/=contador;
        }
    }
}

void Terreno::display()
{
//    glColor3f(1.0f,0.0f,0.0f);
    glInterleavedArrays(GL_T2F_N3F_V3F, sizeof(PuntoTerreno),&lista_puntos[0].s);
    glDrawElements(GL_TRIANGLES, 100*100*6, GL_UNSIGNED_INT,(void*)lista_indices);
}



#endif // TERRENO_H_INCLUDED
