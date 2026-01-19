// Definiciones de todos los diagramas de flujo
const diagramas = {
    // Diagrama 1: main()
    0: {
        titulo: "1. FUNCIÓN: main()",
        archivo: "FinalProject.c",
        descripcion: "Orquesta la aplicación, muestra menú principal y despliega opciones",
        codigo: `start=>start: Inicio
init=>operation: inicializarDatosSterling(zonas)
load=>operation: cargarHistorico(zonas)
menu=>operation: Mostrar Menu Principal
getop=>inputoutput: Solicitar opcion 1-7
checkop=>condition: Opcion?
mon=>operation: req_monitoreoActual()
pred=>operation: req_calcularPredicciones()
alert=>operation: req_mostrarAlertas()
prom=>operation: req_promediosHistoricos()
reco=>operation: req_generarRecomendaciones()
exp=>operation: req_exportarDatos()
save=>operation: guardarHistorico()
checkpred=>condition: predicciones_calculadas?
savep=>operation: guardarPredicciones()
wait=>operation: esperarEnter()
menucheck=>condition: opcion != 7?
exit=>operation: return 0
end=>end: Fin

start->init->load->menu->getop->checkop
checkop(yes, right)->mon
checkop(no)->pred
pred->wait
mon->wait
alert->wait
prom->wait
reco->wait
exp->wait
wait->menucheck
menucheck(yes)->menu
menucheck(no)->save
save->checkpred
checkpred(yes)->savep->exit
checkpred(no)->exit
exit->end`
    },
    
    // Diagrama 2: generarInterpretacionClimatica()
    1: {
        titulo: "2. FUNCIÓN: generarInterpretacionClimatica()",
        archivo: "climate.c",
        descripcion: "Genera descripción textual basada en temperatura y velocidad de viento",
        codigo: `start=>start: Inicio (Zona *z)
temp1=>condition: Temperatura > 30?
temp2=>condition: Temperatura > 20?
tempex=>operation: temp_desc = CalorExtremo
tempmed=>operation: temp_desc = Templado
tempfrio=>operation: temp_desc = Frio
viento1=>condition: Viento < 5?
viento2=>condition: Viento > 15?
vientoest=>operation: viento_desc = Estancamiento
ventodis=>operation: viento_desc = Dispersion
ventonorm=>operation: viento_desc = VentilacionNormal
sprintf=>operation: sprintf(interpretacion, texto)
end=>end: Fin

start->temp1
temp1(yes)->tempex->viento1
temp1(no)->temp2
temp2(yes)->tempmed->viento1
temp2(no)->tempfrio->viento1
viento1(yes)->vientoest->sprintf
viento1(no)->viento2
viento2(yes)->ventodis->sprintf
viento2(no)->ventonorm->sprintf
sprintf->end`
    },
    
    // Diagrama 3: req_calcularPredicciones()
    2: {
        titulo: "3. FUNCIÓN: req_calcularPredicciones()",
        archivo: "climate.c",
        descripcion: "Calcula predicción a 24h con factores climáticos",
        codigo: `start=>start: Inicio
select=>operation: id = seleccionarZona()
checkid=>condition: id == 5?
ret1=>end: Retornar
input=>inputoutput: Ingresar Temp Viento Humedad
genint=>operation: generarInterpretacionClimatica()
loop=>operation: Para i desde 0 hasta NUM_ZONAS
checkwind=>condition: viento_actual(i) == -1?
next=>operation: i++
factor=>operation: factor = 1.0
effwind=>condition: viento(i) < 5.0?
factor1=>operation: factor += 0.20
effwind2=>condition: viento(i) > 15.0?
factor2=>operation: factor -= 0.15
efftemp=>condition: temp(i) > 28.0?
factor3=>operation: factor += 0.15
effhum=>condition: humedad(i) >= 80.0?
factor4=>operation: factor += 0.10
effhum2=>condition: humedad(i) <= 30.0?
factor5=>operation: factor -= 0.05
calcpred=>operation: prediccion_24h = suma * factor
loopcheck=>condition: i < NUM_ZONAS?
setflag=>operation: predicciones_calculadas = 1
end=>end: Fin

start->select->checkid
checkid(yes)->ret1
checkid(no)->input->genint->loop->checkwind
checkwind(yes)->next->loopcheck
checkwind(no)->factor->effwind
effwind(yes)->factor1->efftemp
effwind(no)->effwind2
effwind2(yes)->factor2->efftemp
effwind2(no)->efftemp
efftemp(yes)->factor3->effhum
efftemp(no)->effhum
effhum(yes)->factor4->calcpred
effhum(no)->effhum2
effhum2(yes)->factor5->calcpred
effhum2(no)->calcpred
calcpred->next
loopcheck(yes)->checkwind
loopcheck(no)->setflag->end`
    },
    
    // Diagrama 4: req_monitoreoActual()
    3: {
        titulo: "4. FUNCIÓN: req_monitoreoActual()",
        archivo: "views.c",
        descripcion: "Muestra niveles actuales de contaminantes vs límites OMS",
        codigo: `start=>start: Inicio
print1=>inputoutput: Imprimir encabezado
loop=>operation: Para i desde 0 hasta NUM_ZONAS
calcexc1=>operation: exc_pm = PM25_actual - LIMITE_PM25
calcexc2=>operation: exc_no2 = NO2_actual - LIMITE_NO2
checkpm=>condition: exc_pm > 0?
statpm=>operation: status_pm = INCUMPLE o CUMPLE
checkno2=>condition: exc_no2 > 0?
statno2=>operation: status_no2 = INCUMPLE o CUMPLE
printrow=>inputoutput: printf resultados
next=>operation: i++
loopcheck=>condition: i < NUM_ZONAS?
printnote=>inputoutput: Imprimir nota SO2
end=>end: Fin

start->print1->loop->calcexc1->calcexc2
calcexc2->checkpm
checkpm(yes)->statpm
checkpm(no)->statpm
statpm->checkno2
checkno2(yes)->statno2
checkno2(no)->statno2
statno2->printrow->next->loopcheck
loopcheck(yes)->calcexc1
loopcheck(no)->printnote->end`
    },
    
    // Diagrama 5: req_mostrarAlertas()
    4: {
        titulo: "5. FUNCIÓN: req_mostrarAlertas()",
        archivo: "views.c",
        descripcion: "Muestra alertas actuales y preventivas basadas en OMS",
        codigo: `start=>start: Inicio
print1=>inputoutput: TABLERO DE RIESGOS OMS
loop=>operation: Para i desde 0 hasta NUM_ZONAS
calcexc1=>operation: exc_pm = PM25_actual - LIMITE
calcexc2=>operation: exc_no2 = NO2_actual - LIMITE
checkno2crit=>condition: exc_no2 > 100?
alertcrit=>inputoutput: CRITICO
checkno2al=>condition: exc_no2 > 0?
alertno2=>inputoutput: ALERTA NO2
checkpm=>condition: exc_pm > 0?
alertpm=>inputoutput: ALERTA PM25
checkboth=>condition: PM25 <= 0 Y NO2 <= 0?
alertok=>inputoutput: OK
next=>operation: i++
loopcheck=>condition: i < NUM_ZONAS?
end=>end: Fin

start->print1->loop->calcexc1->calcexc2->checkno2crit
checkno2crit(yes)->alertcrit->checkpm
checkno2crit(no)->checkno2al
checkno2al(yes)->alertno2->checkpm
checkno2al(no)->checkpm
checkpm(yes)->alertpm->checkboth
checkpm(no)->checkboth
checkboth(yes)->alertok->next
checkboth(no)->next
next->loopcheck
loopcheck(yes)->calcexc1
loopcheck(no)->end`
    },
    
    // Diagrama 6: req_promediosHistoricos()
    5: {
        titulo: "6. FUNCIÓN: req_promediosHistoricos()",
        archivo: "views.c",
        descripcion: "Calcula promedios de 30 días para PM2.5 y NO2",
        codigo: `start=>start: Inicio
print1=>inputoutput: PROMEDIOS 30 DIAS
print2=>inputoutput: Imprimir limites OMS
loop=>operation: Para i desde 0 hasta NUM_ZONAS
initavg=>operation: avg_pm = 0, avg_no2 = 0
loopdias=>operation: Para d desde 0 hasta DIAS
sumpm=>operation: avg_pm += historico pm25
sumno2=>operation: avg_no2 += historico no2
nextdia=>operation: d++
diacheck=>condition: d < DIAS?
divavg=>operation: Dividir entre DIAS
checkavgpm=>condition: avg_pm > LIMITE?
statpm=>operation: EXCEDE o CUMPLE
checkavgno2=>condition: avg_no2 > LIMITE?
statno2=>operation: EXCEDE o CUMPLE
printrow=>inputoutput: printf resultados
next=>operation: i++
zonacheck=>condition: i < NUM_ZONAS?
end=>end: Fin

start->print1->print2->loop->initavg->loopdias
loopdias->sumpm->sumno2->nextdia->diacheck
diacheck(yes)->sumpm
diacheck(no)->divavg->checkavgpm
checkavgpm(yes)->statpm
checkavgpm(no)->statpm
statpm->checkavgno2
checkavgno2(yes)->statno2
checkavgno2(no)->statno2
statno2->printrow->next->zonacheck
zonacheck(yes)->initavg
zonacheck(no)->end`
    },
    
    // Diagrama 7: req_generarRecomendaciones()
    6: {
        titulo: "7. FUNCIÓN: req_generarRecomendaciones()",
        archivo: "views.c",
        descripcion: "Muestra recomendaciones dinámicas basadas en excedencias",
        codigo: `start=>start: Inicio
print1=>inputoutput: ESTRATEGIAS DE MITIGACION
loop=>operation: Para i desde 0 hasta NUM_ZONAS
excedepm=>condition: PM25_actual > LIMITE?
actpm=>operation: PM = 1 o 0
excedeno2=>condition: NO2_actual > LIMITE?
actno2=>operation: NO2 = 1 o 0
checkpmexit=>condition: PM O prediccion PM?
actionpm=>inputoutput: Suspender actividades
checkno2exit=>condition: NO2 O prediccion NO2?
actionno2=>inputoutput: Reducir trafico
actionkeep=>inputoutput: Mantener medidas
next=>operation: i++
zonacheck=>condition: i < NUM_ZONAS?
end=>end: Fin

start->print1->loop->excedepm
excedepm(yes)->actpm
excedepm(no)->actpm
actpm->excedeno2
excedeno2(yes)->actno2
excedeno2(no)->actno2
actno2->checkpmexit
checkpmexit(yes)->actionpm->checkno2exit
checkpmexit(no)->checkno2exit
checkno2exit(yes)->actionno2->next
checkno2exit(no)->actionkeep->next
next->zonacheck
zonacheck(yes)->excedepm
zonacheck(no)->end`
    },
    
    // Diagrama 8: req_exportarDatos()
    7: {
        titulo: "8. FUNCIÓN: req_exportarDatos()",
        archivo: "export.c",
        descripcion: "Genera reporte TXT con datos actuales y predicciones",
        codigo: `start=>start: Inicio
open=>operation: fopen(Informe_Sterling.txt, w)
checkopen=>condition: Abierto?
erroropen=>inputoutput: ERROR
header=>inputoutput: fprintf encabezado
checkpred=>condition: predicciones?
writeaviso=>inputoutput: AVISO No disponibles
writeactive=>inputoutput: ESTADO Activa
loopzonas=>operation: Para i desde 0 hasta NUM_ZONAS
writezona=>inputoutput: fprintf ZONA
calcexc=>operation: Calcular excedencias
writeactual=>inputoutput: fprintf niveles actuales
checkclima=>condition: predicciones?
writeclima=>inputoutput: fprintf prediccion 24h
writenodata=>inputoutput: DATOS NO DISPONIBLES
writereco=>inputoutput: fprintf recomendaciones
next=>operation: i++
zonacheck=>condition: i < NUM_ZONAS?
close=>operation: fclose(f)
success=>inputoutput: EXITO
end=>end: Fin

start->open->checkopen
checkopen(yes)->header
checkopen(no)->erroropen->end
header->checkpred
checkpred(yes)->writeactive->loopzonas
checkpred(no)->writeaviso->loopzonas
loopzonas->writezona->calcexc->writeactual->checkclima
checkclima(yes)->writeclima->writereco
checkclima(no)->writenodata->writereco
writereco->next->zonacheck
zonacheck(yes)->writezona
zonacheck(no)->close->success->end`
    },
    
    // Diagrama 9: inicializarDatosSterling()
    8: {
        titulo: "9. FUNCIÓN: inicializarDatosSterling()",
        archivo: "data.c",
        descripcion: "Carga datos iniciales hardcodeados de 5 zonas",
        codigo: `start=>start: Inicio
zone1=>operation: Manhattan PM25=7.7
zone2=>operation: Bronx PM25=6.4
zone3=>operation: Brooklyn PM25=6.4
zone4=>operation: Queens PM25=6.8
zone5=>operation: Staten Island PM25=5.9
loop=>operation: Para i desde 0 hasta NUM_ZONAS
initclima=>operation: Inicializar clima
loopdias=>operation: Para d desde 0 hasta DIAS
calcvar=>operation: var = (d%2) ? 0.98 : 1.02
genhist=>operation: historico = actual * var
nextdia=>operation: d++
diacheck=>condition: d < DIAS?
next=>operation: i++
zonacheck=>condition: i < NUM_ZONAS?
end=>end: Fin

start->zone1->zone2->zone3->zone4->zone5
zone5->loop->initclima->loopdias->calcvar->genhist
genhist->nextdia->diacheck
diacheck(yes)->calcvar
diacheck(no)->next->zonacheck
zonacheck(yes)->initclima
zonacheck(no)->end`
    },
    
    // Diagrama 10: guardarHistorico()
    9: {
        titulo: "10. FUNCIÓN: guardarHistorico()",
        archivo: "data.c",
        descripcion: "Guarda históricos de 30 días en historico.csv",
        codigo: `start=>start: Inicio
open=>operation: fopen(historico.csv, w)
checkopen=>condition: Abierto?
erroropen=>inputoutput: ERROR
loopz=>operation: Para i desde 0 hasta NUM_ZONAS
loopd=>operation: Para d desde 0 hasta DIAS
writeline=>inputoutput: fprintf CSV line
nextd=>operation: d++
dcheck=>condition: d < DIAS?
nextz=>operation: i++
zcheck=>condition: i < NUM_ZONAS?
close=>operation: fclose(f)
end=>end: Fin

start->open->checkopen
checkopen(yes)->loopz
checkopen(no)->erroropen->end
loopz->loopd->writeline->nextd->dcheck
dcheck(yes)->writeline
dcheck(no)->nextz->zcheck
zcheck(yes)->loopd
zcheck(no)->close->end`
    },
    
    // Diagrama 11: cargarHistorico()
    10: {
        titulo: "11. FUNCIÓN: cargarHistorico()",
        archivo: "data.c",
        descripcion: "Lee historico.csv y carga datos si existe",
        codigo: `start=>start: Inicio
open=>operation: fopen(historico.csv, r)
checkopen=>condition: Existe?
ret=>end: Retornar
loop=>operation: Mientras fscanf() lee
parseline=>operation: Parsear linea CSV
validate=>condition: Valido?
next=>operation: Siguiente
assign=>operation: Guardar en historico
loopcheck=>condition: Hay mas?
close=>operation: fclose(f)

start->open->checkopen
checkopen(yes)->loop
checkopen(no)->ret
loop->parseline->validate
validate(yes)->assign->next
validate(no)->next
next->loopcheck
loopcheck(yes)->parseline
loopcheck(no)->close->ret`
    },
    
    // Diagrama 12: guardarPredicciones()
    11: {
        titulo: "12. FUNCIÓN: guardarPredicciones()",
        archivo: "data.c",
        descripcion: "Guarda predicciones de 24h en predicciones.csv",
        codigo: `start=>start: Inicio
open=>operation: fopen(predicciones.csv, w)
checkopen=>condition: Abierto?
erroropen=>inputoutput: ERROR
loop=>operation: Para i desde 0 hasta NUM_ZONAS
writeline=>inputoutput: fprintf linea
next=>operation: i++
zcheck=>condition: i < NUM_ZONAS?
close=>operation: fclose(f)
end=>end: Fin

start->open->checkopen
checkopen(yes)->loop
checkopen(no)->erroropen->end
loop->writeline->next->zcheck
zcheck(yes)->writeline
zcheck(no)->close->end`
    },
    
    // Diagrama 13: seleccionarZona()
    12: {
        titulo: "13. FUNCIÓN: seleccionarZona()",
        archivo: "util.c",
        descripcion: "Menú para elegir una zona (1-5) o volver (6)",
        codigo: `start=>start: Inicio
print1=>inputoutput: Mostrar zonas
loop=>operation: Para i desde 0 hasta NUM_ZONAS
printz=>inputoutput: Mostrar zona i+1
nexti=>operation: i++
icheck=>condition: i < NUM?
printvol=>inputoutput: Mostrar 6. Volver
getinput=>inputoutput: Solicitar opcion
ret=>operation: return opcion - 1
end=>end: Fin

start->print1->loop->printz->nexti->icheck
icheck(yes)->printz
icheck(no)->printvol->getinput->ret->end`
    },
    
    // Diagrama 14: solicitarEntrada()
    13: {
        titulo: "14. FUNCIÓN: solicitarEntrada()",
        archivo: "util.c",
        descripcion: "Lee un float dentro de rango [min, max]",
        codigo: `start=>start: Inicio
loop=>operation: do-while
print=>inputoutput: printf mensaje
read=>inputoutput: fgets entrada
parse=>condition: sscanf OK?
checkrange=>condition: En rango?
ret=>operation: return valor
end=>end: Fin

start->loop->print->read->parse
parse(yes)->checkrange
parse(no)->loop
checkrange(yes)->ret->end
checkrange(no)->loop`
    },
    
    // Diagrama 15: solicitarEntero()
    14: {
        titulo: "15. FUNCIÓN: solicitarEntero()",
        archivo: "util.c",
        descripcion: "Lee un int dentro de rango [min, max]",
        codigo: `start=>start: Inicio
loop=>operation: do-while
print=>inputoutput: printf mensaje
read=>inputoutput: fgets entrada
parse=>condition: sscanf OK?
checkrange=>condition: En rango?
ret=>operation: return valor
end=>end: Fin

start->loop->print->read->parse
parse(yes)->checkrange
parse(no)->loop
checkrange(yes)->ret->end
checkrange(no)->loop`
    },
    
    // Diagrama 16: esperarEnter()
    15: {
        titulo: "16. FUNCIÓN: esperarEnter()",
        archivo: "util.c",
        descripcion: "Pausa el programa esperando que el usuario presione ENTER",
        codigo: `start=>start: Inicio
print=>inputoutput: printf [ENTER] para continuar
wait=>inputoutput: getchar()
end=>end: Fin

start->print->wait->end`
    }
};
