// 製造物データを保持
const products = [];

/* -----------------------------
   製造物追加
----------------------------- */
document.getElementById("addBtn").addEventListener("click", () => {
  const name = document.getElementById("name").value.trim();
  const qty = Number(document.getElementById("qty").value);

  if (!name || qty <= 0) return;

  products.push({
    id: crypto.randomUUID(),
    name,
    qty,
    isOpen: true, // 各 product の開閉状態
    materials: [
      { id: crypto.randomUUID(), name: "", amount: 1 },
      { id: crypto.randomUUID(), name: "", amount: 1 },
      { id: crypto.randomUUID(), name: "", amount: 1 }
    ]
  });

  document.getElementById("name").value = "";
  document.getElementById("qty").value = "1";

  render();
});

/* -----------------------------
   HTML文字のエスケープ
----------------------------- */
function escapeHtml(value) {
  return String(value)
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;")
    .replaceAll("'", "&#39;");
}

/* -----------------------------
   素材の合計計算
----------------------------- */
function aggregate() {
  const result = {};

  // 必要素材を集計
  products.forEach(product => {
    product.materials.forEach(material => {
      const materialName = material.name.trim();
      const amount = Number(material.amount);

      if (!materialName || amount <= 0) return;

      const total = amount * product.qty;

      if (!result[materialName]) {
        result[materialName] = { req: 0, own: 0 };
      }

      result[materialName].req += total;
    });
  });

  // Summary 表に入力された所持数を反映
  document.querySelectorAll(".own").forEach(input => {
    const name = input.dataset.name;
    if (result[name]) {
      result[name].own = Number(input.value) || 0;
    }
  });

  return result;
}

/* -----------------------------
   製造物一覧描画
----------------------------- */
function renderProducts() {
  const el = document.getElementById("products");
  el.innerHTML = "";

  if (products.length === 0) {
    el.innerHTML = `<div class="empty-state">まだ product がありません。</div>`;
    return;
  }

  products.forEach(product => {
    const usedMaterialCount = product.materials.filter(material => material.name.trim() !== "").length;

    const div = document.createElement("div");
    div.className = "product-card";

    div.innerHTML = `
      <div class="product-header">
        <div class="product-header-left">
          <button
            class="toggle-btn"
            onclick="toggleProduct('${product.id}')"
            aria-label="toggle product"
          >
            ${product.isOpen ? "▾" : "▸"}
          </button>

          <div class="product-title-wrap">
            <p class="product-title">${escapeHtml(product.name)}</p>
            <div class="product-meta">
              Quantity: ${product.qty} / Materials in use: ${usedMaterialCount}
            </div>
          </div>
        </div>

        <div class="product-actions">
          <button class="danger-btn" onclick="del('${product.id}')">Delete</button>
        </div>
      </div>

      ${product.isOpen ? `
        <div class="product-body">
          <div class="product-grid">
            <div class="field">
              <label>Product Name</label>
              <input
                value="${escapeHtml(product.name)}"
                onchange="pname('${product.id}', this.value)"
              >
            </div>

            <div class="field">
              <label>Quantity</label>
              <input
                type="number"
                value="${product.qty}"
                min="1"
                onchange="pqty('${product.id}', this.value)"
              >
            </div>
          </div>

          <p class="materials-title">Materials</p>

          <div class="material-list">
            ${product.materials.map((material, index) => `
              <div class="material-row">
                <div class="material-label">Material ${index + 1}</div>

                <input
                  value="${escapeHtml(material.name)}"
                  placeholder="Material name"
                  onchange="mname('${product.id}', '${material.id}', this.value)"
                >

                <input
                  type="number"
                  value="${material.amount}"
                  min="1"
                  onchange="mamt('${product.id}', '${material.id}', this.value)"
                >
              </div>
            `).join("")}
          </div>
        </div>
      ` : ""}
    `;

    el.appendChild(div);
  });
}

/* -----------------------------
   集計テーブル描画
----------------------------- */
function renderSummary() {
  const el = document.getElementById("summary");
  const data = aggregate();
  const keys = Object.keys(data).sort((a, b) => a.localeCompare(b, "ja"));

  if (keys.length === 0) {
    el.innerHTML = `<div class="summary-empty">まだ素材データがありません。</div>`;
    return;
  }

  el.innerHTML = `
    <div class="summary-table-wrap">
      <table>
        <tr>
          <th>Material</th>
          <th>Required</th>
          <th>Owned</th>
          <th>Remain</th>
        </tr>
        ${keys.map(key => {
          const required = data[key].req;
          const owned = data[key].own || 0;
          const remain = Math.max(required - owned, 0);

          return `
            <tr>
              <td>${escapeHtml(key)}</td>
              <td>${required}</td>
              <td>
                <input
                  class="own"
                  data-name="${escapeHtml(key)}"
                  type="number"
                  min="0"
                  value="${owned}"
                  oninput="renderSummary()"
                >
              </td>
              <td class="remain-cell">${remain}</td>
            </tr>
          `;
        }).join("")}
      </table>
    </div>
  `;
}

/* -----------------------------
   全体再描画
----------------------------- */
function render() {
  renderProducts();
  renderSummary();
}

/* -----------------------------
   各種更新処理
----------------------------- */

// 製造物の開閉
function toggleProduct(id) {
  const product = products.find(product => product.id === id);
  if (!product) return;

  product.isOpen = !product.isOpen;
  renderProducts();
}

// 製造物名変更
function pname(id, value) {
  const product = products.find(product => product.id === id);
  if (!product) return;

  product.name = value;
  renderProducts();
  renderSummary();
}

// 個数変更
function pqty(id, value) {
  const product = products.find(product => product.id === id);
  if (!product) return;

  product.qty = Math.max(1, Number(value) || 1);
  renderProducts();
  renderSummary();
}

// 削除
function del(id) {
  const index = products.findIndex(product => product.id === id);
  if (index === -1) return;

  products.splice(index, 1);
  render();
}

// 素材名変更
function mname(productId, materialId, value) {
  const product = products.find(product => product.id === productId);
  if (!product) return;

  const material = product.materials.find(material => material.id === materialId);
  if (!material) return;

  material.name = value;
  renderProducts();
  renderSummary();
}

// 必要数変更
function mamt(productId, materialId, value) {
  const product = products.find(product => product.id === productId);
  if (!product) return;

  const material = product.materials.find(material => material.id === materialId);
  if (!material) return;

  material.amount = Math.max(1, Number(value) || 1);
  renderSummary();
}

// 初期描画
render();