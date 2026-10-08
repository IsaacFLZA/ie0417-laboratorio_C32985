# Laboratorio 2: IntroducciÃ³n prÃ¡ctica a contenedores con Docker

**Curso:** IE0417 - DiseÃ±o de Software para IngenierÃ­a  
**Tema:** Contenedores y Docker  
**Modalidad:** Individual  


## Ãndice

1. [Parte 1: VerificaciÃ³n de instalaciÃ³n de Docker](parte1-verificacion.md)
2. [Parte 2: Primer contenedor](parte2-comandos-basicos.md)
3. [Parte 3: ImÃ¡genes y contenedores](parte3-imagenes-y-contenedores.md)
4. [Parte 4: AdministraciÃ³n de contenedores](parte3-imagenes-y-contenedores.md#administraciÃ³n-de-contenedores)
5. [Parte 5: AplicaciÃ³n Flask](parte4-dockerfile.md)
6. [Parte 6: ConstrucciÃ³n de una imagen con Dockerfile](parte4-dockerfile.md)
7. [Parte 7: PublicaciÃ³n de puertos](parte5-puertos.md)
8. [Parte 8: Logs e inspecciÃ³n](parte5-puertos.md#logs-e-inspecciÃ³n)
9. [Parte 9: Variables de entorno](parte5-puertos.md#variables-de-entorno)
10. [Parte 10: Persistencia con volÃºmenes](parte6-volumenes.md)
11. [Parte 11: Bind mounts](parte6-volumenes.md#bind-mounts)
12. [Parte 12: Redes de Docker](parte7-redes.md)
13. [Parte 13: ComunicaciÃ³n entre servicios](parte7-redes.md#comunicaciÃ³n-entre-servicios)
14. [Parte 14: Limpieza del ambiente](parte8-limpieza.md)

## Estructura del proyecto

```text
laboratorio-contenedores/
â”œâ”€â”€ README.md
â”œâ”€â”€ parte1-verificacion.md
â”œâ”€â”€ parte2-comandos-basicos.md
â”œâ”€â”€ parte3-imagenes-y-contenedores.md
â”œâ”€â”€ parte4-dockerfile.md
â”œâ”€â”€ parte5-puertos.md
â”œâ”€â”€ parte6-volumenes.md
â”œâ”€â”€ parte7-redes.md
â”œâ”€â”€ parte8-limpieza.md
â”œâ”€â”€ evidencias/
â””â”€â”€ app/
    â”œâ”€â”€ Dockerfile
    â”œâ”€â”€ app.py
    â””â”€â”€ requirements.txt
```

## AplicaciÃ³n utilizada

Durante el laboratorio se utilizÃ³ una aplicaciÃ³n sencilla desarrollada con Flask. La aplicaciÃ³n permite comprobar el funcionamiento de un servicio web dentro de un contenedor y practicar conceptos como publicaciÃ³n de puertos, variables de entorno y bind mounts.

La aplicaciÃ³n incluye una ruta principal `/` y una ruta `/info`.

## ReflexiÃ³n final

1. **Â¿QuÃ© es un contenedor?**

   Un contenedor es un entorno aislado donde se puede ejecutar una aplicaciÃ³n junto con los archivos y dependencias que necesita. A diferencia de una mÃ¡quina virtual completa, utiliza recursos del sistema anfitriÃ³n y comparte su kernel, lo que permite que sea mÃ¡s ligero y rÃ¡pido de iniciar.

2. **Â¿QuÃ© problema resuelve Docker?**

   Docker ayuda a evitar diferencias entre entornos de desarrollo y ejecuciÃ³n. Permite empaquetar una aplicaciÃ³n junto con sus dependencias para que pueda ejecutarse de forma similar en diferentes equipos que tengan Docker disponible.

3. **Â¿QuÃ© diferencia hay entre una imagen y un contenedor?**

   Una imagen funciona como una plantilla que contiene los archivos y la configuraciÃ³n necesarios para crear un contenedor. Un contenedor es una instancia creada a partir de esa imagen y puede estar ejecutÃ¡ndose o detenida.

4. **Â¿QuÃ© diferencia hay entre un contenedor y una mÃ¡quina virtual?**

   Una mÃ¡quina virtual normalmente incluye un sistema operativo completo con su propio kernel (Hypervisor). Un contenedor es mÃ¡s ligero porque comparte el kernel del sistema anfitriÃ³n y mantiene aislados principalmente los procesos, archivos y recursos necesarios para la aplicaciÃ³n.

5. **Â¿QuÃ© aprendiÃ³ sobre puertos?**

   AprendÃ­ que una aplicaciÃ³n puede escuchar en un puerto dentro del contenedor, pero ese puerto no necesariamente estÃ¡ disponible desde el host. Para acceder al servicio desde fuera del contenedor es necesario publicar o mapear el puerto con una opciÃ³n como `-p 5000:5000`.

   TambiÃ©n aprendÃ­ que el puerto del host y el puerto interno del contenedor no tienen que ser iguales.

6. **Â¿QuÃ© aprendiÃ³ sobre volÃºmenes?**

   AprendÃ­ que los volÃºmenes permiten mantener informaciÃ³n aunque un contenedor sea eliminado. Los datos almacenados en un volumen tienen un ciclo de vida independiente al del contenedor y pueden ser utilizados posteriormente por otro contenedor.

7. **Â¿QuÃ© aprendiÃ³ sobre redes?**

   AprendÃ­ que Docker permite crear redes para conectar varios contenedores. Los contenedores que forman parte de una misma red pueden comunicarse y utilizar nombres para identificar servicios, lo que evita depender directamente de direcciones IP que pueden cambiar.

8. **Â¿En quÃ© casos usarÃ­a Docker en un proyecto de software?**

   UsarÃ­a Docker cuando sea necesario mantener un entorno de ejecuciÃ³n consistente entre distintos desarrolladores o equipos, cuando una aplicaciÃ³n dependa de versiones especÃ­ficas de herramientas o librerÃ­as, o cuando un sistema estÃ© compuesto por varios servicios que convenga mantener separados.

   TambiÃ©n lo utilizarÃ­a para facilitar pruebas, despliegues y configuraciÃ³n de entornos de desarrollo.

9. **Â¿QuÃ© parte del laboratorio le pareciÃ³ mÃ¡s Ãºtil?**

   La parte que me pareciÃ³ mÃ¡s Ãºtil fue construir una imagen propia mediante un Dockerfile y ejecutar la aplicaciÃ³n Flask dentro de un contenedor. Esta parte permitiÃ³ relacionar varios conceptos del laboratorio, como imÃ¡genes, contenedores, dependencias, puertos y configuraciÃ³n.

10. **Â¿QuÃ© parte le pareciÃ³ mÃ¡s confusa?**

    La parte mÃ¡s confusa fue la comunicaciÃ³n entre contenedores mediante redes, porque requiere comprender la diferencia entre la red interna de Docker, los nombres de los contenedores y los puertos publicados hacia el host.

    Sin embargo, las pruebas realizadas ayudaron a entender mejor cÃ³mo se separan estos conceptos y cÃ³mo los distintos servicios pueden comunicarse dentro de una aplicaciÃ³n basada en contenedores. 

