# StockChecker
Program using C language read an external file with specific format then printing the stock that is item that is needed to be restock and the new price after discount

The file has the specific format of the following:

n (number of items)
"Kategori" (category of 1st item)
"Sub-Kategori" (subcategory of 1st item)
"Stok" (the sum of stock of 1st item)
"Harga" (price per item of 1st item)
...
...
...
...
"Kategori" (category of nth item)
"Sub-Kategori" (subcategory of nth item)
"Stok" (the sum of stock of nth item)
"Harga" (price per item of nth item)

Category has 4 types "Baju", "Celana", "Aksesoris", "Sepatu"

Stock need to follow the following rules:
"Baju" need to be Restocked if less than 75 to achieve 150
"Celana" need to be Restocked if less than 50 to achieve 100
"Aksesoris" need to be Restocked if less than 25 to achieve 50
"Sepatu" need to be Restocked if less than 60 to achieve 175

Discount will be given according to following rules:
"Baju" need to be Discounted 35% if more than 150
"Celana" need to be Discounted 50% if more than 100
"Aksesoris" need to be Discounted 10% if more than 50
"Sepatu" need to be Discounted 70% if more than 120

The program will print the category that needed to be restocked and the cheapest items in store