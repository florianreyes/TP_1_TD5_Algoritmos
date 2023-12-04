# TP_1_TD5_Algoritmos

### - El problema
En un instante dado (o en un intervalo muy pequeño de tiempo, digamos 10-15 segundos) y en una determinada área geográfica la empresa posee un número de pedidos de viajes a realizar y una cierta cantidad de vehículos disponibles para realizar viajes. Para cada pasajero podemos asumir la disponibilidad de un mínimo de información como: \n

- el instante en el que realizó el pedido;
- la localización de origen del viaje (donde debe ser buscado);
- la localización de destino del viaje (donde debe ser llevado) o la distancia estimada del recorrido;
- una estimación de la tarifa total a cobrar por el viaje (que depende en parte de la distancia del recorrido, pero puede contener gastos extra como valijas, cantidad de pasajeros, horas pico, etc.)
  
Análogamente, también podemos asumir mínimamente conocer en tiempo real la localización de cada uno de los vehículos de nuestra flota, en particular la de aquellos que estén disponibles para realizar viajes. Combinando la localización de pasajeros y vehículos, podemos asumir también que conocemos la distancia a recorrer que le llevaría a cada vehículo llegar a cada posible cliente a fin de poder empezar el viaje. \n

El problema que buscamos resolver es decidir que vehículo debe buscar a cada pasajero.
A fin de formular un modelo para la decisión en cuestión, primero formalizamos el problema. Tenemos n vehiculos disponibles, $i = 1,...,n$ para cubrir n viajes de distintos pasajeros, j = 1, . . . , n. Por simplicidad, asumimos que el problema se encuentra balanceado en términos de 1
oferta y demanda de viajes.1 En función de la información geográfica de los conductores y pasajeros, definimos dij a la distancia que debe recorrer el conductor i para empezar el viaje del pasajero j. Adicionalmente, para un pasajero j = 1, . . . , n llamamos vj a la distancia del viaje a realizar por el pasajero j y fj a la tarifa total a cobrarle por el viaje. Asumimos también que los pasajeros se encuentran ya ordenados de manera creciente en función del instante en el que realizaron el pedido.
