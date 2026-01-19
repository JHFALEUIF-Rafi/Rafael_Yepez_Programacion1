# SGA-NYC: Sistema Integral de Gestión de Contaminación del Aire

## Descripción
Sistema modular en C para monitoreo, predicción y alerta de contaminación del aire en 5 zonas urbanas de Nueva York (Manhattan, Bronx, Brooklyn, Queens, Staten Island). Implementa análisis de contaminantes (PM2.5, NO2, SO2) con predicciones basadas en datos históricos y factores meteorológicos.

## Estructura del Proyecto

```
├── FinalProject.c          # Función main() y menú principal
├── climate.c               # Predicción climática y análisis atmosférico
├── views.c                 # Vistas (monitoreo, alertas, promedios, recomendaciones)
├── export.c                # Exportación de reportes TXT
├── data.c                  # Inicialización, persistencia (CSV) y carga de datos
├── util.c                  # Funciones de utilidad (entrada de datos, selección)
├── sga.h                   # Encabezado con estructuras, constantes y prototipos
└── docs/                   # Documentación y archivos de entrada (consigna, reportes)
    ├── Consigna.docx
    ├── Consigna_text.txt
    └── ...
```

## Compilación

### Con GCC
```bash
gcc -Wall -Wextra -O2 FinalProject.c climate.c views.c export.c data.c util.c -o FinalProject
```

### Con MSVC (cl)
```bash
cl /Fe:FinalProject.exe FinalProject.c climate.c views.c export.c data.c util.c
```

## Uso

Ejecutar el programa:
```bash
.\FinalProject.exe
```

**Menú principal:**
1. **[Actual]** Monitoreo detallado por región (estado actual vs límites OMS)
2. **[Predicción]** Análisis climático e ingreso de temperatura, viento, humedad
3. **[Alertas]** Tablero de riesgos con alertas preventivas (24h)
4. **[Histórico]** Promedios de 30 días vs límites OMS
5. **[Mitigación]** Estrategias de reducción por zona
6. **[Informe]** Generar reporte técnico (TXT)
7. **[Salir]** Guardar datos y cerrar

## Funcionalidades Clave

### Monitoreo Actual
- Muestra niveles de PM2.5, NO2, SO2 en 5 zonas
- Compara con límites OMS 2021 (PM2.5 < 5.0, NO2 < 10.0, SO2 < 40.0)
- Indica estado "CUMPLE" o "INCUMPLE"

### Predicción Climática
- Ingresa temperatura (°C), viento (km/h), humedad (%)
- Calcula factor de penalización climática:
  - Viento < 5 km/h: +20% (estancamiento)
  - Viento > 15 km/h: −15% (dispersión)
  - Temperatura > 28°C: +15% (reacciones químicas)
  - Humedad ≥ 80%: +10% (partículas y química secundaria)
  - Humedad ≤ 30%: −5% (menos formación secundaria)
- Usa promedio ponderado histórico (últimos 7 días x2, anteriores x1)

### Alertas Preventivas
- Evalúa valores actuales vs OMS
- Emite alertas preventivas si predicción a 24h excede límites
- Clasifica como [OK], [ALERTA], [CRITICO], [PREVENTIVA]

### Recomendaciones Dinámicas
- Acciones base por zona (Ley Local 97, ULEZ, etc.)
- Acciones adicionales si actual o predicción excede:
  - PM2.5: suspender actividades al aire libre
  - NO2: reducción de tráfico, cierre industrial temporal

### Persistencia
- Guarda históricos en `historico.csv` (30 días × 5 zonas)
- Guarda predicciones en `predicciones.csv` (si calculadas)
- Carga automáticamente al iniciar si existen

### Exportación
- Genera reporte `Informe_Sterling_Enero2026.txt` con:
  - Niveles actuales vs OMS
  - Brechas porcentuales (excedancia)
  - Proyecciones a 24h
  - Estrategias de mitigación

## Archivos de Salida

Se generan en la raíz del proyecto (al ejecutar opciones del menú):
- `Informe_Sterling_Enero2026.txt` – Reporte técnico completo
- `historico.csv` – Históricos de contaminantes (CSV)
- `predicciones.csv` – Predicciones calculadas (CSV)

## Requisitos de la Consigna

✅ **Cumplidos:**
- Arreglos, estructuras, punteros, funciones, archivos
- 5 zonas urbanas (mínimo requerido)
- Monitoreo actual vs límites OMS
- Predicción a 24h con factores climáticos (temperatura, viento, humedad)
- Alertas preventivas
- Promedios históricos (30 días)
- Recomendaciones de mitigación
- Exportación de reportes
- Persistencia mediante CSV
- Sin librerías externas (solo estándar C)

## Notas

- Se basan en datos reales de calidad del aire en NYC (enero 2026)
- Límites OMS 2021 aplicados (más estrictos que EPA)
- Modelo predictivo usa ponderación temporal (últimos 7 días con mayor peso)
- Sistema modular facilita agregar más zonas o contaminantes
