It seems that sqlite does them the safest by default, so it don't need to worry (if i have declared that it is a transaction ig) 

Yes, there are ways to ensure that adding a new element to a table doesn't impact a previous query, primarily through the use of **database transactions** and appropriate **isolation levels**.

Here's how it works:

**Transactions and Isolation:**

*   **Transactions:** As explained before, a transaction is a sequence of database operations treated as a single unit of work.
*   **Isolation Levels:** Isolation levels define the degree to which concurrent transactions are isolated from each other. They control how changes made by one transaction are visible to other concurrent transactions.

**How Transactions and Isolation Prevent Interference:**

1.  **Read Committed (Most Common):**
    *   This is the default isolation level in many databases.
    *   A transaction can only see changes that have been committed by other transactions.
    *   If a transaction is reading data while another transaction is modifying it, the reading transaction will only see the data as it was *before* the other transaction started making changes.
    *   This prevents "dirty reads" (reading uncommitted data).

2.  **Repeatable Read:**
    *   This provides stronger isolation than Read Committed.
    *   A transaction sees the same data throughout its execution, even if other transactions commit changes.
    *   This prevents "non-repeatable reads" (where a transaction reads the same row multiple times and gets different results) and "phantom reads" (where a transaction performs a query multiple times and sees new rows appearing).

3.  **Serializable (Strongest Isolation):**
    *   This provides the highest level of isolation.
    *   Transactions are executed as if they were running sequentially, even if they are actually running concurrently.
    *   This prevents all concurrency-related anomalies.

**Example Scenario and Solutions:**

Let's say you have two operations:

1.  **Query:** `SELECT * FROM MyTable WHERE some_column = 'value';`
2.  **Insert:** `INSERT INTO MyTable (some_column, ...) VALUES ('value', ...);`

You want to ensure that if the query runs *before* the insert, it doesn't "see" the newly inserted row.

*   **Solution with Read Committed (Usually Sufficient):**

    ```sql
    -- Transaction 1 (Query)
    BEGIN TRANSACTION;
    SELECT * FROM MyTable WHERE some_column = 'value'; -- Sees the data as it was at the start of this transaction
    COMMIT TRANSACTION;

    -- Transaction 2 (Insert)
    BEGIN TRANSACTION;
    INSERT INTO MyTable (some_column, ...) VALUES ('value', ...);
    COMMIT TRANSACTION;
    ```

    With Read Committed, the query in Transaction 1 will see the data as it was *before* Transaction 2 started. The insert in Transaction 2 will not affect the results of the query.

*   **Solution with Repeatable Read or Serializable (Stronger but Potentially More Overhead):**

    Using Repeatable Read or Serializable would provide even stronger guarantees, ensuring that the query sees a consistent snapshot of the data throughout the entire transaction, even if other transactions are running concurrently. However, these higher isolation levels can sometimes have a performance impact due to increased locking.

**Specific Database System Behavior:**

*   **SQLite:** SQLite's default isolation level is Serializable. This means that concurrent writes are serialized and happen one after the other. This prevents concurrent writes from interfering with each other and reads.
*   **Other Databases (PostgreSQL, MySQL, SQL Server, etc.):** These systems usually default to Read Committed. You can explicitly set the isolation level if needed.

**In summary:**

Using transactions with appropriate isolation levels (usually Read Committed is sufficient) is the way to guarantee that a query is not affected by concurrent inserts or other modifications. The database system handles the necessary locking and concurrency control to ensure data consistency. If you're using SQLite, you already have the benefit of Serializable isolation by default.
