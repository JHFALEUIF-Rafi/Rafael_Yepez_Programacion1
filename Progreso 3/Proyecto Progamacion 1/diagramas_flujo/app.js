// Variables globales
let currentDiagram = 0;
let charts = {};

// Función para renderizar un diagrama
function renderDiagram(index) {
    const diagrama = diagramas[index];
    const containerId = `canvas-${index}`;
    
    // Limpiar el contenedor
    const container = document.getElementById(containerId);
    if (!container) {
        // Crear el contenedor si no existe
        const newContainer = document.createElement('div');
        newContainer.className = 'diagram-container';
        newContainer.id = containerId;
        document.querySelector('.content').appendChild(newContainer);
    }
    
    // Crear el info si no existe
    const infoId = `info-${index}`;
    if (!document.getElementById(infoId)) {
        const infoDiv = document.createElement('div');
        infoDiv.className = 'diagram-info';
        infoDiv.id = infoId;
        infoDiv.innerHTML = `
            <h2>${diagrama.titulo}</h2>
            <div class="info-grid">
                <div><strong>📄 Archivo:</strong> ${diagrama.archivo}</div>
                <div><strong>📝 Descripción:</strong> ${diagrama.descripcion}</div>
            </div>
        `;
        document.querySelector('.content').insertBefore(infoDiv, document.getElementById('canvas-0'));
    }
    
    // Si el diagrama ya fue renderizado, no hacer nada más
    if (charts[index]) {
        return;
    }
    
    try {
        // Parsear y renderizar el diagrama
        const chart = flowchart.parse(diagrama.codigo);
        chart.drawSVG(containerId, {
            'x': 0,
            'y': 0,
            'line-width': 2,
            'line-length': 50,
            'text-margin': 10,
            'font-size': 14,
            'font-family': 'Segoe UI, Arial, sans-serif',
            'font-weight': 'normal',
            'font-color': '#333',
            'line-color': '#667eea',
            'element-color': '#333',
            'fill': '#f9f9f9',
            'yes-text': 'Si',
            'no-text': 'No',
            'arrow-end': 'block',
            'scale': 1,
            'symbols': {
                'start': {
                    'font-color': 'white',
                    'element-color': '#667eea',
                    'fill': '#667eea'
                },
                'end': {
                    'font-color': 'white',
                    'element-color': '#764ba2',
                    'fill': '#764ba2'
                }
            },
            'flowstate': {
                'approved': {
                    'fill': '#58C4A3',
                    'font-color': 'white'
                },
                'rejected': {
                    'fill': '#C45879',
                    'font-color': 'white'
                }
            }
        });
        
        charts[index] = chart;
    } catch (error) {
        console.error(`Error renderizando diagrama ${index}:`, error);
        document.getElementById(containerId).innerHTML = `
            <div style="padding: 20px; color: red; text-align: center;">
                <h3>Error al renderizar el diagrama</h3>
                <p>${error.message}</p>
            </div>
        `;
    }
}

// Función para mostrar un diagrama específico
function showDiagram(index) {
    currentDiagram = index;
    
    // Ocultar todos los diagramas e info
    document.querySelectorAll('.diagram-container').forEach(el => {
        el.classList.remove('active');
    });
    document.querySelectorAll('.diagram-info').forEach(el => {
        el.classList.remove('active');
    });
    
    // Remover clase active de todos los botones
    document.querySelectorAll('.tab-button').forEach(btn => {
        btn.classList.remove('active');
    });
    
    // Activar el botón seleccionado
    const buttons = document.querySelectorAll('.tab-button');
    if (buttons[index]) {
        buttons[index].classList.add('active');
    }
    
    // Mostrar el info y diagrama seleccionado
    const infoElement = document.getElementById(`info-${index}`);
    if (infoElement) {
        infoElement.classList.add('active');
    }
    
    const canvasElement = document.getElementById(`canvas-${index}`);
    if (canvasElement) {
        canvasElement.classList.add('active');
    }
    
    // Renderizar el diagrama si no se ha hecho aún
    if (!charts[index]) {
        renderDiagram(index);
    }
    
    // Scroll hacia arriba
    window.scrollTo({ top: 0, behavior: 'smooth' });
}

// Inicialización cuando carga la página
window.addEventListener('load', function() {
    console.log('Página cargada, inicializando diagramas...');
    
    // Crear todos los contenedores
    for (let i = 0; i < 16; i++) {
        const diagrama = diagramas[i];
        
        // Crear info
        if (i > 0) { // El primero ya existe en el HTML
            const infoDiv = document.createElement('div');
            infoDiv.className = 'diagram-info';
            infoDiv.id = `info-${i}`;
            infoDiv.innerHTML = `
                <h2>${diagrama.titulo}</h2>
                <div class="info-grid">
                    <div><strong>📄 Archivo:</strong> ${diagrama.archivo}</div>
                    <div><strong>📝 Descripción:</strong> ${diagrama.descripcion}</div>
                </div>
            `;
            document.querySelector('.content').appendChild(infoDiv);
        }
        
        // Crear contenedor de canvas
        if (i > 0) { // El primero ya existe en el HTML
            const container = document.createElement('div');
            container.className = 'diagram-container';
            container.id = `canvas-${i}`;
            document.querySelector('.content').appendChild(container);
        }
    }
    
    // Renderizar el primer diagrama
    showDiagram(0);
    
    console.log('Inicialización completada');
});

// Función para convertir SVG a PNG y retornar el blob
function svgToCanvas(svgElement) {
    return new Promise((resolve, reject) => {
        try {
            const svgData = new XMLSerializer().serializeToString(svgElement);
            const canvas = document.createElement('canvas');
            const ctx = canvas.getContext('2d');
            const img = new Image();
            
            // Obtener dimensiones del SVG
            const bbox = svgElement.getBBox();
            const width = Math.ceil(bbox.width) + 40;
            const height = Math.ceil(bbox.height) + 40;
            
            canvas.width = width;
            canvas.height = height;
            
            // Fondo blanco
            ctx.fillStyle = 'white';
            ctx.fillRect(0, 0, width, height);
            
            img.onload = function() {
                ctx.drawImage(img, 20, 20);
                canvas.toBlob(function(blob) {
                    resolve(blob);
                }, 'image/png', 0.95);
            };
            
            img.onerror = reject;
            img.src = 'data:image/svg+xml;base64,' + btoa(unescape(encodeURIComponent(svgData)));
        } catch (error) {
            reject(error);
        }
    });
}

// Función para descargar un archivo
function downloadBlob(blob, fileName) {
    return new Promise((resolve) => {
        const url = URL.createObjectURL(blob);
        const link = document.createElement('a');
        link.download = fileName;
        link.href = url;
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
        
        // Esperar a que la descarga se registre
        setTimeout(() => {
            URL.revokeObjectURL(url);
            resolve();
        }, 500);
    });
}

// Función para convertir SVG a PNG y descargar (antigua)
function exportSVGtoPNG(svgElement, fileName) {
    return new Promise((resolve, reject) => {
        try {
            const svgData = new XMLSerializer().serializeToString(svgElement);
            const canvas = document.createElement('canvas');
            const ctx = canvas.getContext('2d');
            const img = new Image();
            
            // Obtener dimensiones del SVG
            const bbox = svgElement.getBBox();
            const width = bbox.width + 40;
            const height = bbox.height + 40;
            
            canvas.width = width;
            canvas.height = height;
            
            // Fondo blanco
            ctx.fillStyle = 'white';
            ctx.fillRect(0, 0, width, height);
            
            img.onload = function() {
                ctx.drawImage(img, 20, 20);
                canvas.toBlob(function(blob) {
                    const url = URL.createObjectURL(blob);
                    const link = document.createElement('a');
                    link.download = fileName;
                    link.href = url;
                    link.click();
                    URL.revokeObjectURL(url);
                    resolve();
                }, 'image/png');
            };
            
            img.onerror = reject;
            img.src = 'data:image/svg+xml;base64,' + btoa(unescape(encodeURIComponent(svgData)));
        } catch (error) {
            reject(error);
        }
    });
}

// Función para exportar el diagrama actual
function exportCurrentDiagram() {
    const containerId = `canvas-${currentDiagram}`;
    const container = document.getElementById(containerId);
    const svgElement = container.querySelector('svg');
    
    if (!svgElement) {
        alert('Por favor espera a que el diagrama se cargue completamente');
        return;
    }
    
    const diagrama = diagramas[currentDiagram];
    const fileName = `diagrama_${currentDiagram + 1}_${diagrama.titulo.replace(/[^a-zA-Z0-9]/g, '_')}.png`;
    
    exportSVGtoPNG(svgElement, fileName)
        .then(() => {
            console.log(`Diagrama ${currentDiagram + 1} exportado exitosamente`);
        })
        .catch(error => {
            console.error('Error al exportar:', error);
            alert('Error al exportar el diagrama. Por favor intenta de nuevo.');
        });
}

// Función para exportar todos los diagramas
async function exportAllDiagrams() {
    const button = event.target;
    const originalText = button.textContent;
    button.disabled = true;
    
    try {
        let totalRendered = 0;
        
        // PASO 1: Renderizar todos los diagramas
        console.log('Renderizando todos los diagramas...');
        button.textContent = '⏳ Renderizando diagramas...';
        
        for (let i = 0; i < 16; i++) {
            if (!charts[i]) {
                console.log(`Renderizando diagrama ${i + 1}/16...`);
                showDiagram(i);
                // Esperar a que Raphael renderice
                await new Promise(resolve => setTimeout(resolve, 800));
                totalRendered++;
            }
        }
        
        console.log(`Total renderizados: ${totalRendered}`);
        
        // PASO 2: Exportar todos los diagramas secuencialmente
        console.log('Iniciando exportación...');
        let successCount = 0;
        
        for (let i = 0; i < 16; i++) {
            try {
                const containerId = `canvas-${i}`;
                const container = document.getElementById(containerId);
                
                if (!container) {
                    console.warn(`Contenedor ${containerId} no encontrado`);
                    continue;
                }
                
                const svgElement = container.querySelector('svg');
                
                if (!svgElement) {
                    console.warn(`SVG en contenedor ${containerId} no encontrado`);
                    continue;
                }
                
                console.log(`Exportando diagrama ${i + 1}/16...`);
                button.textContent = `⏳ Descargando... (${i + 1}/16)`;
                
                const diagrama = diagramas[i];
                const cleanName = diagrama.titulo
                    .replace(/[^a-zA-Z0-9]/g, '_')
                    .replace(/_+/g, '_')
                    .substring(0, 40);
                const fileName = `diagrama_${String(i + 1).padStart(2, '0')}_${cleanName}.png`;
                
                // Convertir SVG a blob
                const blob = await svgToCanvas(svgElement);
                
                // Descargar
                await downloadBlob(blob, fileName);
                
                successCount++;
                console.log(`✓ Diagrama ${i + 1} descargado: ${fileName}`);
                
                // Esperar antes de la siguiente descarga
                await new Promise(resolve => setTimeout(resolve, 1200));
                
            } catch (error) {
                console.error(`Error exportando diagrama ${i + 1}:`, error);
            }
        }
        
        // Resultado final
        if (successCount === 16) {
            button.textContent = '✅ ¡16 Diagramas Descargados!';
            setTimeout(() => {
                button.textContent = originalText;
                button.disabled = false;
            }, 3000);
        } else {
            button.textContent = `✅ ${successCount}/16 Diagramas Descargados`;
            setTimeout(() => {
                button.textContent = originalText;
                button.disabled = false;
            }, 3000);
        }
        
        console.log(`Exportación completada: ${successCount}/16 diagramas`);
        
    } catch (error) {
        console.error('Error durante la exportación:', error);
        button.textContent = '❌ Error en exportación';
        setTimeout(() => {
            button.textContent = originalText;
            button.disabled = false;
        }, 3000);
    }
}
