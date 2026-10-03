# Parte 5: aplicación sencilla con Flask

<!-- Documentacion requerida (borrar este comentario al terminar):
- [ ] Qué hace la aplicación
- [ ] Qué rutas tiene
- [ ] Qué dependencia utiliza
- [ ] Por qué se usa host="0.0.0.0" en lugar de localhost
-->

## Qué hace la aplicación


## Rutas


## Dependencia utilizada


## Por qué host="0.0.0.0"


## Paso: Prueba local (opcional, si tienes Python)

**Qué se hizo:**

**Comando ejecutado:**

```bash
pip install -r requirements.txt
python app.py
# abrir http://localhost:5000
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Preguntas de reflexión

1. **¿Qué hace Flask en esta aplicación?**

   Respuesta: 

2. **¿Para qué sirve el archivo requirements.txt?**

   Respuesta: 

3. **¿Por qué una aplicación dentro de un contenedor debe escuchar en 0.0.0.0?**

   Respuesta: 

4. **¿Qué diferencia hay entre ejecutar la aplicación localmente y ejecutarla dentro de Docker?**

   Respuesta: 


---

# Parte 6: construir una imagen con Dockerfile

<!-- Documentacion requerida (borrar este comentario al terminar):
- [ ] Documentar cada instrucción: FROM, WORKDIR, COPY, RUN, EXPOSE, CMD
- [ ] Qué significa construir una imagen
- [ ] Qué significa el nombre laboratorio-flask:1.0
- [ ] Diferencia entre nombre de imagen y nombre de contenedor
- [ ] Resultado de docker images
-->

## Instrucciones del Dockerfile

- **FROM:** 
- **WORKDIR:** 
- **COPY:** 
- **RUN:** 
- **EXPOSE:** 
- **CMD:** 

## Qué significa construir una imagen


## Qué significa laboratorio-flask:1.0


## Nombre de la imagen vs. nombre del contenedor


## Paso: docker build (ejecutar dentro de app/)

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker build -t laboratorio-flask:1.0 .
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: docker images

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker images
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Ejecutar el contenedor (terminal 1)

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run --name app-lab laboratorio-flask:1.0
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Revisar contenedores (terminal 2)

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker ps
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Detener y eliminar

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker stop app-lab
docker rm app-lab
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

### Preguntas de reflexión (Dockerfile)

1. **¿Qué es una imagen base?**

   Respuesta: 

2. **¿Por qué se usa una imagen slim?**

   Respuesta: 

3. **¿Por qué se copian primero las dependencias y luego el resto del código?**

   Respuesta: 

4. **¿Qué diferencia hay entre RUN y CMD?**

   Respuesta: 

5. **¿Qué pasaría si se elimina la imagen pero no el Dockerfile?**

   Respuesta: 

