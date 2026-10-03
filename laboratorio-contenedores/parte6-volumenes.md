# Parte 10: persistencia con volúmenes

<!-- Documentacion requerida (borrar este comentario al terminar):
- [ ] Qué es un volumen
- [ ] Cómo se crea
- [ ] Cómo se monta en un contenedor
- [ ] Qué pasó con el archivo después de eliminar el primer contenedor
- [ ] Resultado de docker volume inspect
-->

## Paso: Crear y listar el volumen

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker volume create datos-lab
docker volume ls
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Primer contenedor montando el volumen

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -it --name contenedor-volumen -v datos-lab:/datos ubuntu bash
# dentro del contenedor:
echo "Este archivo está en un volumen" > /datos/archivo.txt
cat /datos/archivo.txt
exit
# ya fuera:
docker rm contenedor-volumen
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Segundo contenedor con el mismo volumen

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run -it --name contenedor-volumen-2 -v datos-lab:/datos ubuntu bash
# dentro del contenedor:
cat /datos/archivo.txt
exit
# ya fuera:
docker rm contenedor-volumen-2
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Inspeccionar el volumen

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker volume inspect datos-lab
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Preguntas de reflexión

1. **¿Qué problema resuelven los volúmenes?**

   Respuesta: 

2. **¿El volumen pertenece a un contenedor específico?**

   Respuesta: 

3. **¿Qué diferencia hay entre eliminar un contenedor y eliminar un volumen?**

   Respuesta: 

4. **¿Para qué casos reales se usarían volúmenes?**

   Respuesta: 


---

## Bind mounts

<!-- Parte 11. Documentar: diferencia entre datos-lab:/datos y "$(pwd)":/app; qué ocurrió al modificar el código local; por qué esto puede ser útil durante el desarrollo. -->

## Paso: Bind mount desde la carpeta app/ (en PowerShell usar ${PWD})

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run --name app-bind -p 5000:5000 -v ${PWD}:/app laboratorio-flask:1.0
# abrir http://localhost:5000
# modificar app.py en el host (por ejemplo el mensaje HTML)
docker stop app-bind
docker rm app-bind
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

## Paso: Volver a ejecutar y comprobar el cambio

**Qué se hizo:**

**Comando ejecutado:**

```bash
docker run --name app-bind-2 -p 5000:5000 -v ${PWD}:/app laboratorio-flask:1.0
# abrir http://localhost:5000
docker stop app-bind-2
docker rm app-bind-2
```

**Explicación (para qué sirve el comando):**

**Resultado obtenido** (salida copiada de la terminal o captura):

```text

```

**Reflexión:**

### Preguntas de reflexión (bind mounts)

1. **¿Qué diferencia hay entre un volumen y un bind mount?**

   Respuesta: 

2. **¿Cuál parece más conveniente para desarrollo?**

   Respuesta: 

3. **¿Cuál parece más conveniente para datos persistentes de una aplicación?**

   Respuesta: 

4. **¿Qué riesgos podría tener montar carpetas del host dentro del contenedor?**

   Respuesta: 

