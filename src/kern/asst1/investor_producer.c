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
	// only change the servedby value of the item and return a structure pointer
	// the structure name is: order; it will hold the begin and end of the order items from list



	return NULL; //modify
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
	(void)v;
	panic("You need to write some code!!!!");
}

/*
 * serve_order()
 *
 * Takes a produced item and makes it available to the waiting customer.
 */

void serve_order(void *v, unsigned long producernumber)
{
	(void)v;
	(void)producernumber;
	panic("You need to write some code!!!!");
}

/**
 * calculate_loan_amount()
 * Calculate loan amount
 */
long int calculate_loan_amount(void *itm)
{
	(void)itm;
	panic("You need to write some code!!!!");
	return 0;
}

/**
 * void loan_request()
 * Request for loan from bank
 */
void loan_request(void *amount, unsigned long producernumber)
{
	(void)amount;
	(void)producernumber;
	panic("You need to write some code!!!!");
}

/**
 * loan_reimburse()
 * Return loan amount and service charge
 */
void loan_reimburse(void *loan, unsigned long producernumber)
{
	(void)loan;
	(void)producernumber;
	panic("You need to write some code!!!!");
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

void initialize()
{
	panic("You need to write some code!!!!");
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
