# Diagramas de Flujo - Proyecto SGA-NYC
## Todos los diagramas en formato Mermaid para mermaid.live

---

## 1. FUNCIÓN: main()
**Archivo:** FinalProject.c  
**Descripción:** Orquesta la aplicación, muestra menú principal y despliega opciones.

```mermaid
flowchart TD
    Start([Inicio]) --> Init["inicializarDatosSterling(zonas)"]
    Init --> Load["cargarHistorico(zonas)"]
    Load --> Menu["Mostrar Menú Principal"]
    Menu --> GetOp["solicitarEntero opción 1-7"]
    GetOp --> CheckOp{¿Opción?}
    
    CheckOp -->|1| Mon["req_monitoreoActual()"]
    CheckOp -->|2| Pred["req_calcularPredicciones()"]
    CheckOp -->|3| Alert["req_mostrarAlertas()"]
    CheckOp -->|4| Prom["req_promediosHistoricos()"]
    CheckOp -->|5| Reco["req_generarRecomendaciones()"]
    CheckOp -->|6| Exp["req_exportarDatos()"]
    CheckOp -->|7| Save["guardarHistorico()"]
    
    Mon --> Wait["esperarEnter()"]
    Pred --> Wait
    Alert --> Wait
    Prom --> Wait
    Reco --> Wait
    Exp --> Wait
    
    Save --> SavePred{¿predicciones_calculadas?}
    SavePred -->|Sí| SaveP["guardarPredicciones()"]
    SavePred -->|No| Exit["Retornar 0"]
    SaveP --> Exit
    
    Wait --> MenuCheck{¿opción != 7?}
    MenuCheck -->|Sí| Menu
    MenuCheck -->|No| Exit
    Exit --> End([Fin])
```

---

## 2. FUNCIÓN: generarInterpretacionClimatica()
**Archivo:** climate.c  
**Descripción:** Genera descripción textual basada en temperatura y velocidad de viento.

```mermaid
flowchart TD
    Start([Inicio: Zona *z]) --> TempCheck{¿Temperatura > 30?}
    
    TempCheck -->|Sí| TempEx["temp_desc = 'Calor Extremo'"]
    TempCheck -->|No| TempCheck2{¿Temperatura > 20?}
    TempCheck2 -->|Sí| TempMed["temp_desc = 'Templado'"]
    TempCheck2 -->|No| TempFrio["temp_desc = 'Frio'"]
    
    TempEx --> VientoCheck{¿Viento < 5?}
    TempMed --> VientoCheck
    TempFrio --> VientoCheck
    
    VientoCheck -->|Sí| VientoEst["viento_desc = 'Estancamiento'"]
    VientoCheck -->|No| VientoCheck2{¿Viento > 15?}
    VientoCheck2 -->|Sí| VientoDis["viento_desc = 'Dispersión'"]
    VientoCheck2 -->|No| VientoNorm["viento_desc = 'Ventilación normal'"]
    
    VientoEst --> Sprintf["sprintf(interpretacion, '%s con %s'...)"]
    VientoDis --> Sprintf
    VientoNorm --> Sprintf
    
    Sprintf --> End([Fin])
```

---

## 3. FUNCIÓN: req_calcularPredicciones()
**Archivo:** climate.c  
**Descripción:** Calcula predicción a 24h con factores climáticos (viento, temperatura, humedad).

```mermaid
flowchart TD
    Start([Inicio]) --> Select["id = seleccionarZona()"]
    Select --> CheckId{¿id == 5?}
    CheckId -->|Sí| Return1([Retornar])
    CheckId -->|No| Input["Ingresar: Temp, Viento, Humedad"]
    
    Input --> GenInterpret["generarInterpretacionClimatica()"]
    GenInterpret --> Loop["Para i = 0 a NUM_ZONAS"]
    
    Loop --> CheckWind{¿viento_actual[i] == -1?}
    CheckWind -->|Sí| NextZona["i++"]
    CheckWind -->|No| Factor["factor = 1.0"]
    
    Factor --> EffWind{¿viento[i] < 5.0?}
    EffWind -->|Sí| Factor1["factor += 0.20 (estancamiento)"]
    EffWind -->|No| EffWind2{¿viento[i] > 15.0?}
    EffWind2 -->|Sí| Factor2["factor -= 0.15 (dispersión)"]
    EffWind2 -->|No| EffTemp
    
    Factor1 --> EffTemp{¿temp[i] > 28.0?}
    Factor2 --> EffTemp
    
    EffTemp -->|Sí| Factor3["factor += 0.15 (calor)"]
    EffTemp -->|No| EffHum
    
    Factor3 --> EffHum{¿humedad[i] >= 80.0?}
    EffHum -->|Sí| Factor4["factor += 0.10 (humedad alta)"]
    EffHum -->|No| EffHum2{¿humedad[i] <= 30.0?}
    EffHum2 -->|Sí| Factor5["factor -= 0.05 (humedad baja)"]
    EffHum2 -->|No| SumHist
    
    Factor4 --> SumHist["Sumar históricos ponderados (últimos 7d x2)"]
    Factor5 --> SumHist
    EffHum --> SumHist
    
    SumHist --> CalcPred["prediccion_24h = (suma/pesos) * factor"]
    CalcPred --> NextZona
    NextZona --> LoopCheck{¿i < NUM_ZONAS?}
    LoopCheck -->|Sí| CheckWind
    LoopCheck -->|No| SetFlag["predicciones_calculadas = 1"]
    SetFlag --> End([Fin])
```

---

## 4. FUNCIÓN: req_monitoreoActual()
**Archivo:** views.c  
**Descripción:** Muestra niveles actuales de contaminantes vs límites OMS para todas las zonas.

```mermaid
flowchart TD
    Start([Inicio]) --> Print1["Imprimir encabezado (NIVELES ACTUALES)"]
    Print1 --> Loop["Para i = 0 a NUM_ZONAS"]
    
    Loop --> CalcExc1["exc_pm = (PM25_actual - LIMITE_PM25) / LIMITE_PM25 * 100"]
    CalcExc1 --> CalcExc2["exc_no2 = (NO2_actual - LIMITE_NO2) / LIMITE_NO2 * 100"]
    
    CalcExc2 --> CheckPM{¿exc_pm > 0?}
    CheckPM -->|Sí| StatPM["status_pm = 'INCUMPLE'"]
    CheckPM -->|No| StatPM["status_pm = 'CUMPLE'"]
    
    StatPM --> CheckNO2{¿exc_no2 > 0?}
    CheckNO2 -->|Sí| StatNO2["status_no2 = 'INCUMPLE'"]
    CheckNO2 -->|No| StatNO2["status_no2 = 'CUMPLE'"]
    
    StatNO2 --> PrintRow["printf(zona, contexto, PM25, status_pm, NO2, status_no2)"]
    PrintRow --> NextZona["i++"]
    NextZona --> LoopCheck{¿i < NUM_ZONAS?}
    LoopCheck -->|Sí| CalcExc1
    LoopCheck -->|No| PrintNote["Imprimir nota SO2"]
    PrintNote --> End([Fin])
```

---

## 5. FUNCIÓN: req_mostrarAlertas()
**Archivo:** views.c  
**Descripción:** Muestra alertas actuales y preventivas (24h) basadas en OMS.

```mermaid
flowchart TD
    Start([Inicio]) --> Print1["Imprimir: TABLERO DE RIESGOS OMS"]
    Print1 --> Loop["Para i = 0 a NUM_ZONAS"]
    
    Loop --> CalcExc1["exc_pm = (PM25_actual - LIMITE) / LIMITE * 100"]
    CalcExc1 --> CalcExc2["exc_no2 = (NO2_actual - LIMITE) / LIMITE * 100"]
    
    CalcExc2 --> CheckNO2Crit{¿exc_no2 > 100?}
    CheckNO2Crit -->|Sí| AlertCrit["Imprimir CRITICO"]
    CheckNO2Crit -->|No| CheckNO2Al{¿exc_no2 > 0?}
    CheckNO2Al -->|Sí| AlertNO2["Imprimir ALERTA NO2"]
    CheckNO2Al -->|No| NextCheck
    
    AlertCrit --> CheckPM{¿exc_pm > 0?}
    AlertNO2 --> CheckPM
    NextCheck --> CheckPM
    
    CheckPM -->|Sí| AlertPM["Imprimir ALERTA PM25"]
    CheckPM -->|No| CheckBoth{¿PM25 <= 0 Y NO2 <= 0?}
    
    AlertPM --> CheckBoth
    CheckBoth -->|Sí| AlertOk["Imprimir OK"]
    CheckBoth -->|No| CheckPred
    AlertOk --> CheckPred
    
    CheckPred{¿predicciones_calculadas Y viento != -1?}
    CheckPred -->|No| NextZona["i++"]
    CheckPred -->|Sí| CalcPred1["exc_pm_pred = (PM25_pred - LIMITE) / LIMITE * 100"]
    
    CalcPred1 --> CalcPred2["exc_no2_pred = (NO2_pred - LIMITE) / LIMITE * 100"]
    CalcPred2 --> CheckPredExc{¿exc_pm_pred > 0 O exc_no2_pred > 0?}
    
    CheckPredExc -->|Sí| AlertPrev["Imprimir PREVENTIVA"]
    CheckPredExc -->|No| AlertProj["Imprimir PROYECCION (OK)"]
    
    AlertPrev --> NextZona
    AlertProj --> NextZona
    NextZona --> LoopCheck{¿i < NUM_ZONAS?}
    LoopCheck -->|Sí| CalcExc1
    LoopCheck -->|No| End([Fin])
```

---

## 6. FUNCIÓN: req_promediosHistoricos()
**Archivo:** views.c  
**Descripción:** Calcula promedios de 30 días para PM2.5 y NO2, compara con OMS.

```mermaid
flowchart TD
    Start([Inicio]) --> Print1["Imprimir: PROMEDIOS 30 DIAS VS OMS"]
    Print1 --> Print2["Imprimir límites OMS"]
    Print2 --> Loop["Para i = 0 a NUM_ZONAS"]
    
    Loop --> InitAvg["avg_pm = 0, avg_no2 = 0"]
    InitAvg --> LoopDias["Para d = 0 a DIAS_HISTORICOS"]
    
    LoopDias --> SumPM["avg_pm += historico[i][d].pm25"]
    SumPM --> SumNO2["avg_no2 += historico[i][d].no2"]
    SumNO2 --> NextDia["d++"]
    NextDia --> DiaCheck{¿d < DIAS_HISTORICOS?}
    DiaCheck -->|Sí| SumPM
    DiaCheck -->|No| DivAvg1["avg_pm /= DIAS_HISTORICOS"]
    
    DivAvg1 --> DivAvg2["avg_no2 /= DIAS_HISTORICOS"]
    DivAvg2 --> CheckAvgPM{¿avg_pm > LIMITE_PM25?}
    
    CheckAvgPM -->|Sí| StatPM["status_pm = 'EXCEDE'"]
    CheckAvgPM -->|No| StatPM["status_pm = 'CUMPLE'"]
    
    StatPM --> CheckAvgNO2{¿avg_no2 > LIMITE_NO2?}
    CheckAvgNO2 -->|Sí| StatNO2["status_no2 = 'EXCEDE'"]
    CheckAvgNO2 -->|No| StatNO2["status_no2 = 'CUMPLE'"]
    
    StatNO2 --> PrintRow["printf(zona, avg_pm, status_pm, avg_no2, status_no2)"]
    PrintRow --> NextZona["i++"]
    NextZona --> ZonaCheck{¿i < NUM_ZONAS?}
    ZonaCheck -->|Sí| InitAvg
    ZonaCheck -->|No| End([Fin])
```

---

## 7. FUNCIÓN: req_generarRecomendaciones()
**Archivo:** views.c  
**Descripción:** Muestra recomendaciones dinámicas basadas en excedencias actuales y predichas.

```mermaid
flowchart TD
    Start([Inicio]) --> Print1["Imprimir: ESTRATEGIAS DE MITIGACION"]
    Print1 --> Loop["Para i = 0 a NUM_ZONAS"]
    
    Loop --> ExcedeAct1{¿PM25_actual > LIMITE?}
    ExcedeAct1 -->|Sí| ActPM["excede_actual_pm = 1"]
    ExcedeAct1 -->|No| ActPM["excede_actual_pm = 0"]
    
    ActPM --> ExcedeAct2{¿NO2_actual > LIMITE?}
    ExcedeAct2 -->|Sí| ActNO2["excede_actual_no2 = 1"]
    ExcedeAct2 -->|No| ActNO2["excede_actual_no2 = 0"]
    
    ActNO2 --> CheckPred{¿predicciones_calculadas Y viento != -1?}
    CheckPred -->|No| PredPM["excede_pred_pm = 0, excede_pred_no2 = 0"]
    CheckPred -->|Sí| ExcedePred1{¿PM25_pred > LIMITE?}
    
    ExcedePred1 -->|Sí| PredPM1["excede_pred_pm = 1"]
    ExcedePred1 -->|No| PredPM1["excede_pred_pm = 0"]
    
    PredPM1 --> ExcedePred2{¿NO2_pred > LIMITE?}
    ExcedePred2 -->|Sí| PredNO2["excede_pred_no2 = 1"]
    ExcedePred2 -->|No| PredNO2["excede_pred_no2 = 0"]
    
    PredPM --> PrintBase["printf(ZONA + ACCION BASE)"]
    PredNO2 --> PrintBase
    
    PrintBase --> CheckPMExit{¿excede_actual_pm O excede_pred_pm?}
    CheckPMExit -->|Sí| ActionPM["printf(ACCION: Suspender actividades)"]
    CheckPMExit -->|No| CheckNO2Exit
    
    ActionPM --> CheckNO2Exit{¿excede_actual_no2 O excede_pred_no2?}
    CheckNO2Exit -->|Sí| ActionNO2["printf(ACCION: Reducir tráfico)"]
    CheckNO2Exit -->|No| CheckAll
    
    ActionNO2 --> CheckAll{¿Todos los excedentes en 0?}
    CheckAll -->|Sí| ActionKeep["printf(ACCION: Mantener medidas)"]
    CheckAll -->|No| NextZona["i++"]
    ActionKeep --> NextZona
    NextZona --> ZonaCheck{¿i < NUM_ZONAS?}
    ZonaCheck -->|Sí| ExcedeAct1
    ZonaCheck -->|No| End([Fin])
```

---

## 8. FUNCIÓN: req_exportarDatos()
**Archivo:** export.c  
**Descripción:** Genera reporte TXT con datos actuales, predicciones y recomendaciones.

```mermaid
flowchart TD
    Start([Inicio]) --> Open["FILE *f = fopen('Informe_Sterling_Enero2026.txt', 'w')"]
    Open --> CheckOpen{¿Archivo abierto?}
    CheckOpen -->|No| ErrorOpen["printf(ERROR), return"]
    CheckOpen -->|Sí| Header["fprintf(encabezado oficial)"]
    
    ErrorOpen --> End([Fin])
    Header --> CheckPred{¿predicciones_calculadas?}
    
    CheckPred -->|No| WriteAviso["fprintf(AVISO: Predicciones no disponibles)"]
    CheckPred -->|Sí| WriteActive["fprintf(ESTADO: Simulación activa)"]
    
    WriteAviso --> LoopZonas["Para i = 0 a NUM_ZONAS"]
    WriteActive --> LoopZonas
    
    LoopZonas --> WriteZona["fprintf(ZONA + contexto)"]
    WriteZona --> CalcExc1["exc_pm = (PM25 - LIMITE) / LIMITE * 100"]
    CalcExc1 --> CalcExc2["exc_no2 = (NO2 - LIMITE) / LIMITE * 100"]
    
    CalcExc2 --> CheckPMStat{¿exc_pm > 0?}
    CheckPMStat -->|Sí| StatPM1["stat_pm = 'INCUMPLE'"]
    CheckPMStat -->|No| StatPM1["stat_pm = 'CUMPLE'"]
    
    StatPM1 --> CheckNO2Stat{¿exc_no2 > 0?}
    CheckNO2Stat -->|Sí| StatNO21["stat_no2 = 'INCUMPLE'"]
    CheckNO2Stat -->|No| StatNO21["stat_no2 = 'CUMPLE'"]
    
    StatNO21 --> WriteActual["fprintf(Niveles actuales + estado)"]
    WriteActual --> CheckClima{¿predicciones_calculadas Y viento != -1?}
    
    CheckClima -->|Sí| WriteClima["fprintf(Condiciones + predicción 24h)"]
    CheckClima -->|No| WriteNoData["fprintf(DATOS NO DISPONIBLES)"]
    
    WriteClima --> WriteReco
    WriteNoData --> WriteReco["fprintf(Estrategia de mitigación)"]
    
    WriteReco --> NextZona["i++"]
    NextZona --> ZonaCheck{¿i < NUM_ZONAS?}
    ZonaCheck -->|Sí| WriteZona
    ZonaCheck -->|No| WriteNote["fprintf(Nota especial QUEENS)"]
    
    WriteNote --> Close["fclose(f)"]
    Close --> PrintSuccess["printf(EXITO: Informe generado)"]
    PrintSuccess --> End
```

---

## 9. FUNCIÓN: inicializarDatosSterling()
**Archivo:** data.c  
**Descripción:** Carga datos iniciales hardcodeados de 5 zonas y genera históricos.

```mermaid
flowchart TD
    Start([Inicio]) --> Zone1["Zona 0: Manhattan - PM25=7.7, NO2=27.0, SO2=2.0"]
    Zone1 --> Zone2["Zona 1: Bronx - PM25=6.4, NO2=20.0, SO2=2.1"]
    Zone2 --> Zone3["Zona 2: Brooklyn - PM25=6.4, NO2=19.0, SO2=2.2"]
    Zone3 --> Zone4["Zona 3: Queens - PM25=6.8, NO2=16.5, SO2=2.5"]
    Zone4 --> Zone5["Zona 4: Staten Island - PM25=5.9, NO2=11.0, SO2=1.5"]
    
    Zone5 --> Loop["Para i = 0 a NUM_ZONAS"]
    Loop --> InitClima["Inicializar clima_actual (viento=-1, temp=0, humedad=0)"]
    InitClima --> LoopDias["Para d = 0 a DIAS_HISTORICOS"]
    
    LoopDias --> CalcVar["var = (d%2==0) ? 0.98 : 1.02"]
    CalcVar --> GenHist1["historico[i][d].pm25 = actual[i].pm25 * var"]
    GenHist1 --> GenHist2["historico[i][d].no2 = actual[i].no2 * var"]
    GenHist2 --> GenHist3["historico[i][d].so2 = actual[i].so2"]
    
    GenHist3 --> NextDia["d++"]
    NextDia --> DiaCheck{¿d < DIAS_HISTORICOS?}
    DiaCheck -->|Sí| CalcVar
    DiaCheck -->|No| NextZona["i++"]
    
    NextZona --> ZonaCheck{¿i < NUM_ZONAS?}
    ZonaCheck -->|Sí| InitClima
    ZonaCheck -->|No| End([Fin: Datos cargados])
```

---

## 10. FUNCIÓN: guardarHistorico()
**Archivo:** data.c  
**Descripción:** Guarda históricos de 30 días en historico.csv (CSV).

```mermaid
flowchart TD
    Start([Inicio]) --> Open["FILE *f = fopen('historico.csv', 'w')"]
    Open --> CheckOpen{¿Archivo abierto?}
    CheckOpen -->|No| ErrorOpen["printf(ERROR), return"]
    CheckOpen -->|Sí| LoopZ["Para i = 0 a NUM_ZONAS"]
    
    ErrorOpen --> End([Fin])
    LoopZ --> LoopD["Para d = 0 a DIAS_HISTORICOS"]
    
    LoopD --> WriteLine["fprintf(f, '%d,%d,%.3f,%.3f,%.3f',..."]
    WriteLine --> NextD["d++"]
    NextD --> DCheck{¿d < DIAS_HISTORICOS?}
    DCheck -->|Sí| WriteLine
    DCheck -->|No| NextZ["i++"]
    
    NextZ --> ZCheck{¿i < NUM_ZONAS?}
    ZCheck -->|Sí| LoopD
    ZCheck -->|No| Close["fclose(f)"]
    Close --> End
```

---

## 11. FUNCIÓN: cargarHistorico()
**Archivo:** data.c  
**Descripción:** Lee historico.csv y carga datos si existe.

```mermaid
flowchart TD
    Start([Inicio]) --> Open["FILE *f = fopen('historico.csv', 'r')"]
    Open --> CheckOpen{¿Archivo existe?}
    CheckOpen -->|No| Return([Retornar])
    CheckOpen -->|Sí| Loop["Mientras fscanf() lee línea"]
    
    Loop --> ParseLine["Parsear: id_zona, id_dia, pm25, no2, so2"]
    ParseLine --> Validate{¿Índices válidos?}
    Validate -->|No| NextLine["Siguiente línea"]
    Validate -->|Sí| Assign["historico[zona][dia] = valores leídos"]
    
    Assign --> NextLine
    NextLine --> LoopCheck{¿Hay más líneas?}
    LoopCheck -->|Sí| ParseLine
    LoopCheck -->|No| Close["fclose(f)"]
    
    Close --> Return
```

---

## 12. FUNCIÓN: guardarPredicciones()
**Archivo:** data.c  
**Descripción:** Guarda predicciones de 24h en predicciones.csv.

```mermaid
flowchart TD
    Start([Inicio]) --> Open["FILE *f = fopen('predicciones.csv', 'w')"]
    Open --> CheckOpen{¿Archivo abierto?}
    CheckOpen -->|No| ErrorOpen["printf(ERROR), return"]
    CheckOpen -->|Sí| Loop["Para i = 0 a NUM_ZONAS"]
    
    ErrorOpen --> End([Fin])
    Loop --> WriteLine["fprintf(f, '%d,%.3f,%.3f,%.3f',..."]
    WriteLine --> NextZ["i++"]
    NextZ --> ZCheck{¿i < NUM_ZONAS?}
    ZCheck -->|Sí| WriteLine
    ZCheck -->|No| Close["fclose(f)"]
    
    Close --> End
```

---

## 13. FUNCIÓN: seleccionarZona()
**Archivo:** util.c  
**Descripción:** Menú para elegir una zona (1-5) o volver (6).

```mermaid
flowchart TD
    Start([Inicio]) --> Print1["printf('Seleccione Zona para Clima:')"]
    Print1 --> Loop["Para i = 0 a NUM_ZONAS"]
    Loop --> PrintZ["printf(i+1 + '. ' + zona[i].nombre)"]
    PrintZ --> NextI["i++"]
    NextI --> ICheck{¿i < NUM_ZONAS?}
    ICheck -->|Sí| PrintZ
    ICheck -->|No| PrintVol["printf('6. Volver')"]
    
    PrintVol --> GetInput["opcion = solicitarEntero('Opcion: ', 1, 6)"]
    GetInput --> Return["return opcion - 1"]
    Return --> End([Fin])
```

---

## 14. FUNCIÓN: solicitarEntrada()
**Archivo:** util.c  
**Descripción:** Lee un float dentro de rango [min, max], reintenta si es inválido.

```mermaid
flowchart TD
    Start([Inicio]) --> Loop["do-while"]
    Loop --> Print["printf(mensaje)"]
    Print --> Read["fgets(buffer, BUFFER_SIZE, stdin)"]
    Read --> Parse{¿sscanf() lee float?}
    
    Parse -->|No| Loop
    Parse -->|Sí| CheckRange{¿val >= min Y val <= max?}
    
    CheckRange -->|No| Loop
    CheckRange -->|Sí| Return["return val"]
    Return --> End([Fin])
```

---

## 15. FUNCIÓN: solicitarEntero()
**Archivo:** util.c  
**Descripción:** Lee un int dentro de rango [min, max], reintenta si es inválido.

```mermaid
flowchart TD
    Start([Inicio]) --> Loop["do-while"]
    Loop --> Print["printf(mensaje)"]
    Print --> Read["fgets(buffer, BUFFER_SIZE, stdin)"]
    Read --> Parse{¿sscanf() lee int?}
    
    Parse -->|No| Loop
    Parse -->|Sí| CheckRange{¿val >= min Y val <= max?}
    
    CheckRange -->|No| Loop
    CheckRange -->|Sí| Return["return val"]
    Return --> End([Fin])
```

---

## 16. FUNCIÓN: esperarEnter()
**Archivo:** util.c  
**Descripción:** Pausa el programa esperando que el usuario presione ENTER.

```mermaid
flowchart TD
    Start([Inicio]) --> Print["printf('[ENTER] para continuar...')"]
    Print --> Wait["getchar()"]
    Wait --> End([Fin])
```

---

## RESUMEN DE FUNCIONES

| # | Función | Archivo | Descripción | Líneas |
|---|----------|---------|-------------|--------|
| 1 | main() | FinalProject.c | Orquestación y menú principal | ~60 |
| 2 | generarInterpretacionClimatica() | climate.c | Genera descripción textual de clima | ~15 |
| 3 | req_calcularPredicciones() | climate.c | Predicción a 24h con factores climáticos | ~60 |
| 4 | req_monitoreoActual() | views.c | Muestra niveles actuales | ~20 |
| 5 | req_mostrarAlertas() | views.c | Tablero de riesgos y alertas preventivas | ~30 |
| 6 | req_promediosHistoricos() | views.c | Promedios 30 días vs OMS | ~25 |
| 7 | req_generarRecomendaciones() | views.c | Acciones dinámicas por zona | ~35 |
| 8 | req_exportarDatos() | export.c | Genera reporte TXT meticuloso | ~80 |
| 9 | inicializarDatosSterling() | data.c | Carga datos iniciales + históricos | ~70 |
| 10 | guardarHistorico() | data.c | Escribe historico.csv | ~15 |
| 11 | cargarHistorico() | data.c | Lee historico.csv | ~15 |
| 12 | guardarPredicciones() | data.c | Escribe predicciones.csv | ~15 |
| 13 | seleccionarZona() | util.c | Menú de selección de zona | ~10 |
| 14 | solicitarEntrada() | util.c | Entrada de float validada | ~12 |
| 15 | solicitarEntero() | util.c | Entrada de int validada | ~12 |
| 16 | esperarEnter() | util.c | Pausa hasta ENTER | ~1 |

---

## CÓMO USAR EN MERMAID.LIVE

1. Ve a [https://mermaid.live](https://mermaid.live)
2. Copia el código Mermaid de cada función desde la sección correspondiente (entre los triples backticks ``` ```mermaid```)
3. Pégalo en el editor Mermaid.live
4. El diagrama se renderizará automáticamente
5. Puedes descargar como PNG/SVG desde el botón de descarga

Cada diagrama muestra:
- **Nodos redondeados []()**: Inicio/Fin
- **Rectángulos []**: Procesos/Asignaciones
- **Rombos {}**: Decisiones/Condiciones
- **Flechas**: Flujo de control con etiquetas (Sí/No para decisiones)
