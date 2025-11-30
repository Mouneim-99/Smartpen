document.getElementById("fileInput").addEventListener("change", function(event) {
    const file = event.target.files[0];
    const reader = new FileReader();

    reader.onload = function(e) {
        const text = e.target.result;
        document.getElementById("output").textContent = text;
    };

    reader.readAsText(file);
});
