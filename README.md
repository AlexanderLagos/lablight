# LabLight · Ley del inverso del cuadrado

Laboratorio digital de óptica para estudiantes de primer y segundo año de Física General. El estudiante mide la intensidad lumínica de una fuente a 5 distancias y comprueba si los datos siguen la ley **I = k/d²**.

- **Interfaz en línea:** https://alexanderlagos.github.io/lablight/
- **Repositorio:** https://github.com/AlexanderLagos/lablight
- **Grupo:** Legend · Proyecto de Innovación Tecnológica

## Cómo usar el laboratorio

1. Abre el link de la interfaz (Chrome o Edge recomendados).
2. En **Configura el experimento**, elige la fuente de datos:
   - **Simulación:** no necesita hardware. Puedes ajustar la potencia de la fuente (k), el ruido del sensor y la luz ambiente.
   - **Sensor BH1750 conectado por USB:** conecta el Arduino, presiona **Conectar sensor** y elige el puerto.
3. Presiona **Iniciar experimento**. Con el sensor real, primero apaga la fuente y presiona **Calibrar cero**.
4. Coloca el sensor en la distancia que indica la pantalla (0,20 · 0,30 · 0,40 · 0,50 · 0,60 m) y presiona **Medir**. El sistema toma 5 repeticiones de 10 lecturas cada una, a 10 Hz.
5. Presiona **Siguiente distancia** hasta completar las 5 y luego **Ver resultados**.
6. En **Resultados** verás:
   - el gráfico I vs. d con la curva ajustada;
   - una tabla con el promedio, la desviación estándar, la I teórica y el error %;
   - k ajustado, R² y el exponente n;
   - una conclusión automática.
7. **Repetir experimento** vuelve a medir con los mismos parámetros. **Cambiar parámetros** vuelve a la configuración.

## Usar el sensor real (BH1750)

| BH1750 (GY-302) | Arduino Uno |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

1. Instala el [Arduino IDE](https://www.arduino.cc/en/software).
2. Ve a *Herramientas → Administrar bibliotecas* e instala **BH1750** de Christopher Laws.
3. Abre `firmware/lablight_bh1750/lablight_bh1750.ino`, elige la placa **Arduino Uno** y el puerto, y súbelo.
4. Comprueba en el Monitor Serie (9600 baudios) que aparecen valores en lux. Luego **cierra el Monitor Serie**: si queda abierto, bloquea el puerto.
5. Abre la interfaz y elige *Sensor BH1750 conectado por USB*.

La conexión usa la Web Serial API. Solo funciona en Chrome o Edge de computador y requiere abrir la página por `https` (el link de GitHub Pages). En celulares y en otros navegadores solo está disponible el modo simulación.

## Estructura del repositorio

```
lablight/
├── index.html                  Interfaz completa (HTML + CSS + JavaScript, sin dependencias)
├── firmware/
│   └── lablight_bh1750/
│       └── lablight_bh1750.ino Lectura del BH1750 y envío por serial
├── docs/
│   └── stack.md                Arquitectura y stack tecnológico (texto para el informe)
└── bitacora/                   Bitácoras semanales del equipo (PDF)
```

## Motor de datos

| Paso | Cálculo |
|---|---|
| Calibración de cero | Promedio de 10 lecturas con la fuente apagada. Este valor se resta de todas las lecturas. |
| Filtro | Cada repetición es el promedio de 10 lecturas (1 s a 10 Hz). |
| Estadística por distancia | Media y desviación estándar muestral de las 5 repeticiones. |
| Ajuste del modelo | k por mínimos cuadrados con I = k/d²: k = Σ(Iᵢ/dᵢ²) / Σ(1/dᵢ⁴). |
| Bondad del ajuste | R² = 1 − SS_res/SS_tot. |
| Exponente | Regresión lineal de ln I vs. ln d. La pendiente n debería ser cercana a −2. |
| Error % | \|I medida − I teórica\| / I teórica × 100. |

## Publicar la interfaz (GitHub Pages)

En el repositorio, ve a *Settings → Pages → Build and deployment*. Elige *Deploy from a branch*, rama `main` y carpeta `/ (root)`. En uno o dos minutos la interfaz queda en `https://<usuario>.github.io/<repositorio>/`.

## Equipo y roles

| Integrante | Rol principal | Apoyo |
|---|---|---|
| Martinna Meléndez | Líder del proyecto / Product Owner | Pedagógico/Documentación |
| Manuel Morales | Responsable científico | Software/Datos |
| Alonso Arenas | Hardware/Instrumentación | UX/UI |
| Alexander Lagos | Software/Datos | UX/UI |
| Cristian Ramos | UX/UI | Hardware |
| Francisca Ortega | Pedagógico/Documentación | Entregas |
| Daniel Ysea | Software/Datos | Datos (Python) |
