#include <types.h>
#include <lib.h>
#include <synch.h>
#include <test.h>
#include <thread.h>

#include "investor_producer.h"
#include "invest_assignment.h"

/*
 * **********************************************************************
 * YOU ARE FREE TO CHANGE THIS FILE BELOW THIS POINT AS YOU SEE FIT
 *
 */

/*
 * **********************************************************************
 * FUNCTIONS EXECUTED BY CUSTOMER THREADS
 * **********************************************************************
 */

/*
 * order_item()
 *
 * Takes one argument specifying the item produces. The function
 * makes the item order available to producer threads and then blocks until the producers
 * have produced the item with that appropriate for the customers.
 *
 * The item itself contains the number of ordered items.
 */

void order_item(void *list, void *itm)
{
	// not nedded anymore (void)itm; // to avoid warning
	// panic("You need to write some code!!!!");

	(struct item *)list;
	(struct item *)itm;

	if (list != NULL)
	{ // item list not empty
		struct item *temp = list;
		while (temp->next != NULL)
			temp = temp->next;

		for (int i = 0; i < N_ITEM_TYPE; i++)
		{
			// add array elements of *itm to list
			temp->next = itm[i];
			temp = temp->next;
		}
		temp->next = NULL;
	}
	else // the list is empty then
	{
		list = itm[0];
		struct item *temp = list;
		for (int i = 1; i < N_ITEM_TYPE; i++)
		{
			// add array elements of *itm to list
			temp->next = itm[i];
			temp = temp->next;
		}
		temp->next = NULL;
	}
}

/**
 * consume_item() 
 * Customer consume items which were served by the producers.
 * affected variables in the order queue, on item quantity, order type, requested by, served by
 * customer should keep records for his/her spending in shopping
 * and update spending account
 **/
int consume_item(void *list, void *customer_spend_array,
				 void *producer_inc_array, unsigned long customernum)
{
	// returns true if all items are consumed, false if item(s) still remains
	(struct item *)list;
	(long int *)customer_spend_array;
	(long int *)producer_inc_array;

	struct item *itm_to_del = list;
	int flag = 1;

	while (itm_to_del != NULL)
	{
		if (itm_to_del->requestedBy == customernum && itm_to_del->order_type == SERVICED)
		{
			if(itm_to_del->prev == NULL && itm_to_del->next == NULL){
				// its the only element left in the list
				list = NULL;
			}
			if (itm_to_del->prev == NULL)
			{
				// its the head of the list
				itm_to_del->next->prev = NULL;
			}
			else if (itm_to_del->next == NULL)
			{
				// its the tail of the list
				itm_to_del->prev->next = NULL;
			}
			else (itm_to_del->prev != NULL){
			{
				// its in the middle of the list
				itm_to_del->prev->next = itm_to_del->next;
				itm_to_del->next->prev = itm_to_del->prev;
			}

			customer_spend_array[customernum] += itm_to_del->i_price * itm_to_del->item_quantity;
			producer_inc_array[itm_to_del->servBy] += itm_to_del->i_price * itm_to_del->item_quantity;
		}
		else if(itm_to_del->requestedBy == customernum && itm_to_del->order_type == REQUEST){
			// meaning item requested by this customer is still not served
			flag = 0;
		}
		itm_to_del = itm_to_del->next;
	}

	return flag;
}

/*
 * end_shoping()
 *
 * This function is called by customers when they go home. It could be
 * used to keep track of the number of remaining customers to allow
 * producer threads to exit when no customers remain.
 */

void end_shoping()
{
	panic("You need to write some code!!!!");
}

/*
 * **********************************************************************
 * FUNCTIONS EXECUTED BY ITEM PRODUCER THREADS
 * **********************************************************************
 */

/*
 * take_order()
 *
 * This function waits for a new order to be submitted by
 * customers. When submitted, it records the details and returns a
 * pointer to something representing the order.
 *
 * The return pointer type is void * to allow freedom of representation
 * of orders.
 *
 * The function can return NULL to signal the producer thread it can now
 * exit as there are no customers nor orders left.
 */

void *take_order(void *list)
{
	(struct item*) list;
	if(list == NULL)
		return NULL;
	// only change the servedby value of the item and return a structure pointer
	// the structure name is: order
	(struct item*)list;
	int count = count_item_not_served(list);
	int order_count;
	it(count <= 3)
		order_count = 1;
	else
		order = count / 3;
	struct order *order_list = NULL;
	struct item *temp = list;
	for(int i=0; i<order_count; i++){
		if(temp->serveBy == -1)
			insert(order_list, temp);
		else
			i--;
		temp = temp->next;
	}

	return order_item;
}

void insert(void *order_list, void *order_item){
	// insert the order item into the order_list
	(struct order *) order_list;
	(struct item *) order_item;
	struct order *temp = order_list;
	if(temp == NULL){
		// the list is empty
		order_list->ptr = order_item;
		order_list->prev = NULL;
		order_list->next = NULL;
		return;
	}
	// else the list is not empty, so insert the order item at the end of the list.
	while(temp->next != NULL)
		temp = temp->next;

	struct order *pointer = (struct order*) malloc(sizeof(struct order));
	temp->next = pointer;
	pointer->prev = temp;
	pointer->next = NULL;
	return;

}

int count_item_not_served(void *list){
	(struct item *) list;
	struct item *temp = list;
	int count = 0;
	while (temp != NULL)
	{
		if(temp->servBy == -1)	// counts only if the item was not yet
			count++;
		temp = temp->next;
	}
	return count;
	
}

/*
 * produce_item()
 *
 * This function produce an item if the investment is available for the product
 *
 */

void produce_item(void *v)
{
	//this function is redundant;
}

/*
 * serve_order()
 *
 * Takes a produced item and makes it available to the waiting customer.
 */

void serve_order(void *v, unsigned long producernumber)
{
	(struct order*)v;
	struct order *temp = v;
	while (temp != NULL)
	{
		temp->ptr->order_type = SERVICED;
		temp = temp->next;
	}
	
}

/**
 * calculate_loan_amount()
 * Calculate loan amount
 */
long int calculate_loan_amount(void *itm)
{
	(struct order *)itm;
	struct order *temp = itm;
	long int tot_price = 0;
	while (temp->next != NULL)
	{
		tot_price += temp->ptr->i_price;
		temp = temp->next;
	}
	long int profit = tot_price * PRODUCT_PROFIT / 100;
	long int loan = (tot_price - profit) / (BANK_INTEREST/100 + 1);
	
	return loan;
}

/**
 * void loan_request()
 * Request for loan from bank
 */
void loan_request(void *bank_acc, void *amount, unsigned long producernumber)
{
	(struct bankdata*) bank_acc;
	(long int*) amount;
	bank_acc->remaining_cash -= *(amount);
	bank_acc->acu_loan_amount += *(amount);
	bank_acc->prod_loan[producernumber] += *(amount);

}

/**
 * loan_reimburse()
 * Return loan amount and service charge
 */
void loan_reimburse(void *bank_data, unsigned long producernumber)
{
	(struct bankdata*) bank_data;
	int prod_loan = bank_data->prod_loan[producernumber];	// how much loan
	int intrst = prod_loan * BANK_INTEREST / 100;	// calculate how much interest for how much loan
	bank_data->interest_amount += intrst;	// pay the interest
	bank_data->acu_loan_amount -= prod_loan;	// pay the loan
	bank_data->prod_loan[producernumber] = 0;	// the loan is cleared
}

/*
 * **********************************************************************
 * INITIALISATION AND CLEANUP FUNCTIONS
 * **********************************************************************
 */

/*
 * initialize()
 *
 * Perform any initialization you need before opening the investor-producer process to
 * producers and customers
 */

void initialize(void *customer, void *producer)
{
	(long int*) customer;
	(long int*) producer;
	for(int i=0; i<NPRODUCER; i++){
		producer[i] = 0;
	}
	for(int i=0; i<NCUSTOMER; i++){
		customer[i] = 0;
	}
}

/*
 * finish()
 *
 * Perform any cleanup investor-producer process after the finish everything and everybody
 * has gone home.
 */

void finish()
{
	panic("You need to write some code!!!!");
}
