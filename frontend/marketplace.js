let cart = [];
let member = false;
let bank = "ABC";

// Product data
const nftProducts = [
    { id: 1, name: "Limited Edition 1", img: "./imgs/i6.png", price: 50 },
    { id: 2, name: "Limited Edition 2", img: "./imgs/i7.png", price: 50 },
    { id: 3, name: "Limited Edition 3", img: "./imgs/i8.png", price: 50 },
    { id: 4, name: "Limited Edition 4", img: "./imgs/1.jpg", price: 50 },
    { id: 5, name: "Limited Edition 5", img: "./imgs/2.jpg", price: 50 },
    { id: 6, name: "Limited Edition 6", img: "./imgs/3.jpg", price: 50 },
    { id: 7, name: "Limited Edition 7", img: "./imgs/4.jpg", price: 50 },
    { id: 8, name: "Limited Edition 8", img: "./imgs/5.jpg", price: 50 },
    { id: 9, name: "Limited Edition 9", img: "./imgs/6.jpg", price: 50 },
    { id: 10, name: "Limited Edition 10", img: "./imgs/7.jpg", price: 50 },
    { id: 11, name: "Limited Edition 11", img: "./imgs/8.jpg", price: 50 }
];

// Cart page modal
const cartPageBtn = document.getElementById('cart-page-btn');
const cartPageModal = document.getElementById('cart-page-modal');
const closeModalBtn = document.querySelector('.close-modal');

cartPageBtn.onclick = () => {
    cartPageModal.style.display = 'block';
    renderNFTList();
};

closeModalBtn.onclick = () => {
    cartPageModal.style.display = 'none';
};

window.onclick = (e) => {
    if (e.target === cartPageModal) cartPageModal.style.display = 'none';
}

// Render NFT list
function renderNFTList() {
    const nftList = document.getElementById('nft-list');
    nftList.innerHTML = '';
    nftProducts.forEach(nft => {
        nftList.innerHTML += `
            <div class="nft-item">
                <img src="${nft.img}" alt="${nft.name}" onerror="this.src='./imgs/i6.png'">
                <h4>${nft.name}</h4>
                <div class="nft-price">${nft.price} ETH</div>
                <button class="add-btn" onclick="addToCartPage(${nft.id})">Add to Cart</button>
            </div>
        `;
    });
}

function addToCartPage(id) {
    const product = nftProducts.find(p => p.id === id);
    if (product) {
        cart.push(product);
        updateCartPage();
    }
}

function removeFromCartPage(index) {
    cart.splice(index, 1);
    updateCartPage();
}

function updateCartPage() {
    const cartPageItems = document.getElementById('cart-page-items');
    cartPageItems.innerHTML = '';
    
    cart.forEach((item, index) => {
        cartPageItems.innerHTML += `
            <div class="cart-item-page" style="padding: 10px; border: 1px solid #ccc; margin: 5px 0; display: flex; justify-content: space-between; align-items: center;">
                <span>${item.name} - ${item.price} ETH</span>
                <button onclick="removeFromCartPage(${index})" style="background: red; color: white; border: none; padding: 5px 10px; cursor: pointer;">Remove</button>
            </div>
        `;
    });
    
    updatePricing();
}

function updatePricing() {
    const subtotal = cart.reduce((sum, item) => sum + item.price, 0);
    document.getElementById('subtotal').textContent = subtotal + ' ETH';
    document.getElementById('total-page').textContent = subtotal + ' ETH';
    document.getElementById('discount-page').textContent = '0 ETH';
}

document.getElementById('apply-coupon-page').addEventListener('click', () => {
    const couponCode = document.getElementById('coupon-page').value;
    const subtotal = cart.reduce((sum, item) => sum + item.price, 0);
    
    let discount = 0;
    if (couponCode === 'NFT20') {
        discount = subtotal * 0.2;
    }
    
    const total = subtotal - discount;
    
    document.getElementById('discount-page').textContent = discount.toFixed(2) + ' ETH';
    document.getElementById('total-page').textContent = total.toFixed(2) + ' ETH';
});

document.getElementById('checkout-page').addEventListener('click', () => {
    alert('Thank you for your purchase! Transaction pending...');
    cart = [];
    updateCartPage();
    cartPageModal.style.display = 'none';
});

// Add to cart from main page
document.querySelectorAll('.add-to-cart').forEach(btn => {
    btn.addEventListener('click', (e) => {
        const id = parseInt(e.target.dataset.id);
        const product = nftProducts.find(p => p.id === id);
        if (product) {
            cart.push(product);
            updateCartDropdown();
        }
    });
});

function updateCartDropdown() {
    const cartItems = document.getElementById('cart-items');
    cartItems.innerHTML = '';
    
    let total = 0;
    cart.forEach((item, index) => {
        total += item.price;
        cartItems.innerHTML += `
            <div style="padding: 5px; border-bottom: 1px solid #333;">
                ${item.name} - ${item.price} ETH
                <button onclick="removeFromCart(${index})" style="float: right; background: red; color: white; border: none; padding: 2px 5px; cursor: pointer; font-size: 0.8rem;">X</button>
            </div>
        `;
    });
    
    document.getElementById('cart-total').textContent = 'Total: ' + total + ' ETH';
    document.getElementById('final-total').textContent = 'Final Total: ' + total + ' ETH';
}

function removeFromCart(index) {
    cart.splice(index, 1);
    updateCartDropdown();
}

document.getElementById('apply-coupon').addEventListener('click', () => {
    const couponCode = document.getElementById('coupon').value;
    const total = cart.reduce((sum, item) => sum + item.price, 0);
    
    let discount = 0;
    if (couponCode === 'NFT20') {
        discount = total * 0.2;
    }
    
    const finalTotal = total - discount;
    
    document.getElementById('discount').textContent = 'Discount: ' + discount.toFixed(2) + ' ETH';
    document.getElementById('final-total').textContent = 'Final Total: ' + finalTotal.toFixed(2) + ' ETH';
});

// Cart icon dropdown
document.getElementById('cart-icon').addEventListener('click', () => {
    const navCart = document.getElementById('nav-cart');
    if (navCart.style.display === 'block') {
        navCart.style.display = 'none';
    } else {
        navCart.style.display = 'block';
    }
});
