# Manual de Mantenimiento: Spiderbot

Este manual describe los procedimientos necesarios para garantizar la operatividad y estabilidad del robot SpiderBot.

---

## 1. Seguridad y Manejo de Energía
El robot funciona mediante una batería LiPo de 7.4V (2S), la cual requiere cuidados específicos para mantener la integridad del sistema.

* **Umbral de Voltaje:** No debe dejar que la batería baje de **6.4 V**  totales para evitar daños permanentes a la bateria.
* **Recargar Bateria:** No debe cargar la bateria encima del robot, ni poner en funcionamiento el robot mientras la bateria carga, ademas no se debe dejar insupervisado la carga por que una sobrecarga puede causar un funcionamiento
  
## 2. Mantenimiento del Sistema Mecánico
Dado que la estructura es de **fabricación propia mediante una impresora 3D**, es vital revisar su correcta impresion y su fatiga mecanica tras usarlo.

### 2.1 Inspección de la Estructura
* **Revision de patas:** cada vez que se vaya a usar conviene revisar las patas, ya que el mecanismo de movimiento requiere de muchas partes moviles propensas a desgaste.
* **Zona de Carga:** Inspeccionar el área de 5 * 5 cm destinada a soportar la carga. Asegurar que no existan grietas por tensión.
* **Tornillería:** Revisar el ajuste de los tornillos en la zona central, y revisar después de cada ciclo de movimiento los tornillos de los motores.

### 2.2 Actuadores comerciales
* **Microservo SG90:** Verificar que el movimiento del servo es correcto. Si el servo "tiembla", revisar la señal de control del Arduino.
* **Motores DC:** Limpiar cualquier residuo en los ejes de los dos motores de continua para evitar que el robot pierda el paralelismo.

## 3. Mantenimiento del Sistema Electrónico y Sensores
La integración de la electrónica es fundamental para la autonomía del robot.

### 3.1 Sensores Ultrasonidos (HC-SR04)
* **Limpieza:** Los 3 sensores deben estar libres de polvo para garantizar la detección de obstáculos en el área de 2 * 2.
* **Alineación:** Asegurar que los sensores para seguir la pared estén perfectamente paralelos al chasis para cumplir la prueba de desplazamiento de $1\text{ m}$.

### 3.2 Sensor IR e Interfaz
* **Interfaz de Usuario:** Verificar que el receptor IR responda correctamente al mando para iniciar y detener el robot según lo requerido.
* **Cableado:** Revisar que los jumpers conectados al **Arduino UNO** no se hayan aflojado por la vibración del movimiento de las patas.

### 3.3 Puente H (TB6612FNG)
* **Gestión Térmica:** Tras realizar movimientos, verificar que el chip no presente sobrecalentamiento excesivo.

## 4. Guía de Solución de Problemas (Mantenimiento Correctivo)

| Problema | Causa Probable | Acción Correctiva |
| :--- | :--- | :--- |
| El robot no se mueve paralelo a la pared. | Sensor HC-SR04 desalineado o lectura errónea. | Limpiar sensor y recalibrar el código embebido. |
| El robot excede el tiempo de 1 min en 1 m. | Batería LiPo baja o fricción excesiva en patas. | Cargar batería o lubricar articulaciones. |
| No esquiva obstáculos en los 2 m². | Fallo en la lógica de evasión o sensor IR bloqueado. | Revisar conexiones del sensor y lógica de programación. |
| El robot se apaga al colocar los 250g. | Sobrecarga en el SG90 o caída de tensión. | Verificar que el servo soporte el torque con la carga puesta. |

---

## 5. Registro de Componentes Críticos
Para cualquier sustitución, utilice componentes con estas especificaciones:
* **Cerebro:** Arduino UNO (Programación Embebida).
* **Potencia:** Puente H TB6612FNG.
* **Sensores:** 3x Ultrasonidos HC-SR04 y 1x Receptor IR.
* **Actuadores:** 2x Motores DC y 1x Microservo SG90.
