import { fromEvent } from 'rxjs';
import { ajax } from 'rxjs/ajax';
import { switchMap, tap } from 'rxjs/operators';

const showDataBtn = document.getElementById('showDataBtn');
const deleteLastRowBtn = document.getElementById('deleteLastRowBtn');
const downloadJsonBtn = document.getElementById('downloadJsonBtn');
const dataContainer = document.getElementById('dataContainer');

function downloadFile(url, filename) {
    const a = document.createElement('a');
    a.href = url;
    a.download = filename;
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
}

fromEvent(showDataBtn, 'click').pipe(
    switchMap(() => ajax('/phones.json')),
    tap(response => {
        //downloadFile('/phones.json', 'phones.json');
    })
).subscribe(
    response => {
        const data = response.response;
        if (typeof data === 'object' && data !== null) {
            const dataArray = Object.entries(data);
            const dataHtml = dataArray.map(([phone, description]) => 
                `<pre>${phone}: ${description}</pre>`
            ).join('');
            dataContainer.innerHTML = dataHtml;
        } else {
            console.error('Ошибка: Данные не являются объектом', data);
        }
    },
    error => {
        console.error('Ошибка при получении данных:', error);
    }
);

fromEvent(deleteLastRowBtn, 'click').subscribe(() => {
    const rows = dataContainer.querySelectorAll('pre');
    if (rows.length > 0) {
        rows[rows.length - 1].remove();
    }
});

fromEvent(downloadJsonBtn, 'click').subscribe(() => {
    window.open('/phones.json', '_blank');
});
