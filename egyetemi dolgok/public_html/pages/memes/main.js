import images from './imgnames.js';

let index = 0

const img = document.querySelector('img')
const prevImage = document.createElement('img')
const nextImage = document.createElement('img')
function nextIndex(i) {
    return (i + 1) % images.length
}
function prevIndex(i) {
    return i === 0 ? images.length - 1 : i - 1
}
function init() {
    img.src = images[0]
    prevImage.src = images[images.length - 1]
    nextImage.src = images[1]
}
function next() {
    index = nextIndex(index)
    prevImage.src = img.src
    img.src = nextImage.src
    nextImage.src = images[nextIndex(index)]
}
function prev() {
    index = prevIndex(index)
    nextImage.src = img.src
    img.src = prevImage.src
    prevImage.src = images[prevIndex(index)]
}
document.addEventListener('keydown', function (e) {
    if (e.key === 'ArrowLeft') {
        prev()
    }
    else if (e.key === 'ArrowRight') {
        next()
    }
})

document.addEventListener('swiped-left', function(e) {
    prev()
});

document.addEventListener('swiped-right', function(e) {
    next()
});

init()

alert("use left and right arrow keys to see more ( on phones swipe)");

