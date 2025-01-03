// namespace puzzle.Repositories;

// using System;
// using Microsoft.Data.Sqlite;

// public class Repository{
//   readonly string connectionString = @"Data Source= habit_base.db";
//   public void Create(){
//     using var connection = new SqliteConnection(connectionString);
//     connection.Open();
//     var tableCommand = connection.CreateCommand();
//     tableCommand.CommandText = @"CREATE TABLE IF NOT EXISTS habb(
//           id INTEGER PRIMARY KEY AUTOINCREMENT,
//           Date TEXT,
//           Event TEXT,
//           Quantity INTEGER
//       )";
//     tableCommand.ExecuteNonQuery();
//     //connection.Close(); //since we're using using, there no need to manually close it
//   }
//   private void GetAllRecords(){
//     Console.Clear();
//     using var connection = new SqliteConnection(connectionString);
//     connection.Open();
//     var tableCommand = connection.CreateCommand();
//     tableCommand.CommandText = $"SELECT * FROM habb ";
//     // var tableData = new List<CrazyEvent>();
//     // var reader = tableCommand.ExecuteReader();
//     // if (reader.HasRows)
//     // { //actually fucking cool that you don't have to make those disgusting get/set functions
//     //   while (reader.Read())
//     //     tableData.Add(new CrazyEvent(reader.GetInt32(0), reader.GetInt32(3), reader.GetString(1), reader.GetString(2))); //numrat aty jane numrat e kolonave, te cilet fillojne nga 0
//     // }
//     // else
//     //   Console.WriteLine("No rows found");
//     // foreach (var row in tableData)
//     // {
//     //   Console.WriteLine($"Id:{row.id} \t Date: {row.date} \t Event: {row.Event} \t quantity: {row.quantity}");
//     // }
//     //tableData[1].date = DateTime.Now;     //it may be declared as public, but it doesn't have a setter, so it's read-only

//   }

//     private void Insert(){
//         Console.Clear();
//     // string date = GetStringInput("\n\nPlease insert the date: (Format: dd-mm-yy). Type 0 to return to Main Menu");
//     // string anEvent = GetStringInput("\nPlease enter the type of event");
//     // int quantity = GetNumberInput("\nPlease enter how many times it occurred within the day");

//     using var connection = new SqliteConnection(connectionString);
//     connection.Open();
//     var tableCommand = connection.CreateCommand();
//     // tableCommand.CommandText = $"INSERT INTO habb(Date, Event, quantity) VALUES('{date}', '{anEvent}', '{quantity}')";
//     tableCommand.ExecuteNonQuery();
//     //connection.Close();
//   }
//   private void Delete(){
//     Console.Clear();
//         // int id = GetNumberInput("\nEnter the id of the event you want to delete");
//     using var connection = new SqliteConnection(connectionString);
//     connection.Open();
//     var tableCommand = connection.CreateCommand();
//     // tableCommand.CommandText = $"DELETE from habb WHERE id = '{id}'";
//     int rowCount = tableCommand.ExecuteNonQuery();
//     if (rowCount == 0)
//       Console.WriteLine("\nA record with such Id doesn't exist");
//     else
//       Console.WriteLine("\nDeletion successful");
//   }
// }