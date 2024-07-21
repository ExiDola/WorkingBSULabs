class THashStorage {
    constructor() {
        this.dataHash = {};
    }

    reset() 
    {
        this.dataHash = {};
    }

    addValue(key, value) {
        this.dataHash[key] = value;
    }

    getValue(key) {
        return this.dataHash[key];
    }

    deleteValue(key) {
        delete this.dataHash[key];
    }

    getKeys() {
        return Object.keys(this.dataHash);
    }
}

const storage = new THashStorage();

function AddValue() {
    var key = prompt("Введите название объекта:");
    var value = prompt("Введите описание объекта:");
    
    if (key && value) {
        if (storage.getValue(key) === undefined) {
            storage.addValue(key, value);
        } else {
            displayError("Такой ключ уже существует!");
        }
    } else {
        displayError("Введите корректные данные!");
    }
}

function DeleteValue() {
    var key = prompt("Введите название объекта:");
    
    if (storage.getValue(key)) {
        storage.deleteValue(key);
        updateDisplay();
    } else {
        displayError("Нет такого ключа!");
    }
}

function GetValueInfo() {
    var key = prompt("Введите название объекта:");
    
    var value = storage.getValue(key);
    
    if (value !== undefined) {
        displayInfo(key + " - " + value);
    } else {
        displayError("Нет информации для ключа: " + key);
    }
}

function ListValues() {
    var keys = storage.getKeys();   
    
    if (keys.length === 0) {
        displayInfo("Хэш пуст");
    } else {
        var allInfo = keys.map(key => key + " - " + storage.getValue(key)).join("<br>");
        displayInfo(allInfo);
    }
}

function updateDisplay() {
    var displayDiv = document.getElementById("display");
    displayDiv.innerHTML = "";
    ListValues(); 
}

function displayInfo(message) {
    var displayDiv = document.getElementById("display");
    displayDiv.innerHTML = message;
}

function displayError(message) {
    var displayDiv = document.getElementById("display");
    displayDiv.textContent = message;
}

window.onload = function() {
    updateDisplay();
};
