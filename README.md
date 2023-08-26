# 💻 Entregables_blackpill_stm32 💾
<img src='https://uelectronics.com/wp-content/uploads/2020/12/STM32F401-STM32F411-Tarjeta-de-Desarrollo-V4.jpg'>

Un microcontrolador es un circuito integrado diseñado para tareas específicas y de bajo consumo.

Estos entregables usan temas vistos durante este curso, en el cual se trabajo con el <a href='https://pdf1.alldatasheet.com/datasheet-pdf/view/929999/STMICROELECTRONICS/STM32F411CEU6.html'> STM32F411</a>.

El primero tiene como finalidad de reproducir una canción haciendo uso de un buzzer pasivo, así como los **timer** y las **interrupciones**.

En el segundo se hace uso de más elementos de hardware con los cuales interactuar como el teclado matricial, un LED RGB, el buzzer y una memoria EPROM, en este caso se utilizó una <a href="https://ww1.microchip.com/downloads/en/devicedoc/atmel-8720-seeprom-at24c512c-datasheet.pdf">AT24C512C</a>, lo que se realizó fue guardar 5 password máximo, de las cuales se pueden realizar varias acciones como guardar, borrar, consultar y mostrarlos.

Lo solicitado fue lo siguiente: 

1. Poder insertar password de 4 digitos y guardar password en memoria

2. Al insertar un password valido encender un LED,en la señal en_signal, hacer un tono el buzzer de 4khz y poner el led rgb en color morado
3. El dispositivo tendra que ser capaz de guardar hasta 5 password en memoria
4. El dispositivo debe de ser capaz de poder eliminar password de una direccion de memoria especifica
5. El dispositivo podra ser capaz de desplegar los password y las direcciones de memoria donde estan almacenados
