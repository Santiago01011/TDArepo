La empresa “La Gran Oferta” todos los meses realiza promociones de diferentes productos y necesita 
una aplicación para establecer las ofertas del mes.  
La política de la empresa es realizar ofertas en función de la fecha de vencimiento de los productos que 
tiene en stock. Para ello desea conocer los productos que tienen en stock más próximo a vencer. 
Para ello la empresa necesita conocer los “n” productos más próximos a vencer. El valor “n” lo establece 
la empresa. En caso que haya más de “n” productos que venzan en la misma fecha se guardan todos. Si 
son de fechas diferentes se guardan sólo los “n” solicitados. 
Se dispone del archivo “stock.dat” el cuál tiene el siguiente formato: 
● codProd: código del producto (6 caracteres) 
● descrip: descripción del producto (25 caracteres) 
● lote: número de lote (entero) 
● fVto: fecha de vencimiento del lote (t_fecha tipo fecha) 
● cant: cantidad en stock (medido en unidades de producto) 
 
Se pide: 
● Crear  el  archivo  “prod_a_vencer.txt”,  guardando  nro.  de  orden (1  el  producto  con  fecha  más 
próxima a vencer) el código del producto y su fecha de vencimiento. [x]
● El archivo “stock.dat” está ordenado por código de producto. Todas las fechas son válidas. [x]
● Realizar un menú: 
○ Generar lote de prueba  [x]
○ Ingresar fecha actual  [x]
○ Mostrar los “n” productos más próximos a vencer [x]
○ Generar archivo “prod_a_vencer.txt” (longitud fija) [x]
■ codProd (6 caracteres) 
■ fVto (dd/mm/aaaa) 
■ cant (10 digitos) 
○ Mostrar  Producto  más  próximo  a  vencer  (si  hay  más  de  1,  mostrar  el  que  tenga  mayor 
cantidad en stock) [x]
○ salir [x]
 
 
NOTA: Optimice el uso de memoria.. 