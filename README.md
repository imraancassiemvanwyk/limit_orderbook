# limit_orderbook
a limit orderbook in C++ with all operations (add, cancel and execute) in O(1)

Since the price levels a stock can occupy are discrete because they can only be multiples of the tick and have limits set on what they
can be means we can store the IDs of orders in a vector and access them very easily. The index of a certain in the vector is pretty simple to find by
dividing the limit of the order by the tick and minus one.

The insertion is done adding the order ID to a doubly linked list in the back of the list this ensures that everything is stored by time essentially making a queue
this also has the added bonus of being O(1) as well adding order to a buy/sell hashmap.

Cancelling is done by having a boolean in the order struct that gets changed and the real cancellation gets handled when an order is executed then it only removes the 
order whem its at the front the queue so that we dont have to iterate through the list to find the delete the order wich is O(n) this makes the complexity of cancelling 
O(1)

Executing the order is done by popping the front of the queue and deleting or changing values in the hashmap which is all O(1)








