#ifndef VECTOR_DINAMICO_H
#define VECTOR_DINAMICO_H

#include <stdbool.h>

typedef struct vd VD;

VD* crear_vd(int tamano_inicial, bool ordenado);
void destruir_vd(VD **vd_direccion);
void imprimir_vd(const VD *vd);
void anadir_vd(VD *vd, int valor);
int  buscar_vd(const VD *vd, int valor);
int  acceder_vd(const VD *vd, int index);
int  acceder_verificado_vd(const VD *vd, int index);
void eliminar_vd(VD *vd, int index);
int  tamano_vd(const VD *vd);
int  cantidad_vd(const VD *vd);

#endif
