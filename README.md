# cc-toolchain

### ¿Cómo configurar el ambiente?

#### Docker

Docker es usado para compilar el proyecto de acuerdo a las necesidades del proyecto

Para instalar docker se pude utilizar la siguiente guia [Install docker engine](https://docs.docker.com/engine/install/)

__Verificar que se cuente con el plugin docker-compose__

### ¿Cómo compilar el proyecto?
Para compilar el proyecto para la arquitectura arm se utiliza el siguiente comando en la raiz del proyecto

`docker-compose -f ./docker-compose.yml up`

Tambien se puede compilar el proyecto para la arquitectura del host mediante el
comando 

`cd src && make CROSS_COMPILE= PREFIX= `

Si se compilo para arm ejecutar make clean antes

### ¿Cómo instalar el proyecto
Para copiar los archivos a la tarjeta de desarrollo se puede utilizar el 
siguiente comando para copiar los archivos mediante scp


`cd src && make install`

