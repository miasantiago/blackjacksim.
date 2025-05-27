//Starter code from hw15 and lab06
//mainprogram is holding the menu for main gameplay of blackjack simulation
//Queue is for records, gameplay code is in functions

#include<iostream>
#include<fstream>
#include<string>
#include "Player.hpp"
#include "card.hpp"
using namespace std;

#define MAX_SIZE 20

struct Round {
  string winner;
  int score;
}; //for holding records

class Queue {
  private:
    int front;
    int back;
    int count;
    Round arr[MAX_SIZE]; //sturct data

  public:
    Queue() {
      front = 0;
      count = 0;
      back = MAX_SIZE - 1;
  }

  bool enqueue(Round val) {

    if (isFull()) {
      return false;
    }

    back = (back + 1) % MAX_SIZE;
    arr[back] = val;
    count += 1; // add val to the queue and update class data
    return true;
  } // enqueue

  Round dequeue() {

    if(isEmpty()) {
      cout << "Error! The queue is empty!" << endl;
      return {"", -1};
    }

    Round item = arr[front]; // remove and return the item at the front of the queue

    if (front == back) {
      front = 0;
      back = MAX_SIZE -1;
    } else {
      front = (front + 1) % MAX_SIZE;
    }

    count -= 1; // update class data
    return item;
  } // dequeue

  bool isEmpty() {

    if (count == 0) {
      return true;
    } else {
      return false; // return true if the queue is empty and false otherwise
    }
  } // isEmpty

  bool isFull() {

    if (count == MAX_SIZE) {
      return true; // return true if the array is full
    } else {
      return false; // return false otherwise
    }
  } // isFull

  void printQueue() { //EDIT
    cout << "Round\tWinner\tScore" << endl;
    cout << "---------------------" << endl;
    for (int i = 0; i < count; i++) {
      int index = (front + i) % MAX_SIZE;
      // print the array indexes and contents from index 0 to index MAX_SIZE - 1
      // for list purposes --> only print what queue has in it
      cout << i + 1 << "\t" << arr[index].winner << "\t" << arr[index].score << endl;
    }
  } // printQueue
// like printQueue but it will save the queue to the output stream savefile instead of
// printing to cout
  void saveQueue(ofstream& savefile) { //EDIT
    if (!(savefile.is_open()) ){
      cout << "No file is open. Returning to main program." << endl;
      return;
    } else {

      savefile << "Round\tWinner\tScore" << endl;
      savefile << "---------------------" << endl;

      for (int i = 0; i < count; i++) {
        int index = (front + i) % MAX_SIZE;
        // print the array indexes and contents from index 0 to index MAX_SIZE - 1
        savefile << i + 1 << "\t" << arr[index].winner << "\t" << arr[index].score << endl;
      }
    }
  }

  // return the number of elements in the Queue
  int size() {
    return count;
  } // size

  // returns the value at the head of the queue but does not change the queue
  Round head() {
    return arr[front];
  } // head

}; // queue class

//grab random card set up code
Card drawcard() {
  string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
  string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
  int s = rand() % 4;
  int r = rand() % 13;

  return Card (ranks[r], suits[s]);
}

int main(int argc, char * argv[]) {

  if (argc < 2) {
    cout << "No filename specified" << endl;
    exit(1);
  } //error for no file

  // open the file
  string filename = argv[1];
  ofstream savefile(filename);
  
  if (savefile.fail()) {
    cout << "Cannot open file: " << filename << endl;
    exit(1);
  } //error for opening file

  Round last; //for holding last round played
  bool lastround = false;

  //Card set up code
  srand(time(0));

  Queue menuq; //make multiple queues for each set of data (ex. round, )
  int option;
  do {
    cout << endl; //can change
    cout << "====Welcome! Blackjack Game Menu: Enter 0 to exit====" << endl;
    cout << "1. Enqueue(): Add round to records?" << endl;
    cout << "2. Dequeue(): Clear game records?" << endl;
    cout << "3. isEmpty(): Check if game records are empty" << endl;
    cout << "4. isFull(): Check if game records are full" << endl;
    cout << "5. size(): Game records length" << endl;
    cout << "6. printQueue(): Print game records" << endl;
    cout << "7. head(): First game record" << endl;
    cout << "8. saveQueue(): Save game record to 20rounds.txt!" << endl;
    cout << "9. PLAY BLACKJACK!" << endl << endl;
    cin >> option;
    cin.ignore();
    switch (option) {
    case 0:
      break;
    case 1:
      cout << "Adding last round:" << endl;
      if (lastround) {
        if (!(menuq.enqueue(last))) {
          cout << "Could not add. Game records full!" << endl;
        } else {
          cout << "Round added to records succesfully!" << endl;
          lastround = false;
        }
      } else {
        cout << "Could not add. No round record exists!" << endl;
      }
      break;
    case 2:
      if (!menuq.isEmpty()) {
        while (!menuq.isEmpty()) {
          menuq.dequeue();
        }
        cout << "Game records cleared!" << endl;
      } else {
        cout << "Game records empty!" << endl;
      }
      break;
    case 3:
      if (menuq.isEmpty()) {
        cout << "Game records are empty!" << endl;
      } else {
        cout << "Not empty! Game records is holding " << menuq.size() << " rounds!" << endl;
      }
      break;
    case 4:
      if (menuq.isFull()) {
        cout << "Game records is full!" << endl;
      } else {
        cout << "Not full! Game records is holding " << menuq.size() << " rounds!" << endl;
      }
      break;
    case 5:
      cout << "Game records is holding " << menuq.size() << " rounds!" << endl;
      break;
    case 6:
      cout << "Displaying all rounds: " << endl;
      menuq.printQueue();
      break;
    case 7:
      cout << "First round record: " << endl;
      if (!menuq.isEmpty()) {
        cout << "Winner: " << menuq.head().winner << endl;
        cout << "Score: " << menuq.head().score << endl;
      } else {
        cout << "No first round!" << endl;
      }
      break;
    case 8:
      cout << "Saving game records to " << filename << endl;
      if (savefile.is_open()) {
        menuq.saveQueue(savefile);
        cout << "Your records saved successfully!" << endl;
        savefile.close();
      } else {
        cout << "Failed to open file! Returning to main." << endl;
      }
      break;
    case 9: {
      //Player set up code

      string playername;
      cout << "Enter your Player Name: " << endl;
      getline(cin, playername);

      Player p1(playername, false);
      p1.reset();

      //Player: Dealer set up code
      Player dealer("Dealer", true);

      //Game play code
      cout << "Game has started, dealer has given 2 cards!" << endl;

      //Assign dealer cards

      Card d1 = drawcard();
      Card d2 = drawcard();

      dealer.hit(d1);
      dealer.hit(d2);
      //assign player 2 cards

      Card card1 = drawcard();
      Card card2 = drawcard();

      p1.hit(card1);
      p1.hit(card2);

      cout << "Your cards are: " << card1.toString() << " and " << card2.toString() << endl;
      cout << "Your score is: " << p1.getScore() << "!" << endl;
      //if its blackjack code
      if(p1.hasBlackjack()) {

        cout << "You got a blackjack!" << endl;
        cout << "You have automatically won the round!!" << endl;
        //set round records
        last.winner = p1.getName();
        last.score = 21;
        lastround = true;
        cout << "Return to main menu to manage game records.. and start a new round!" << endl;
        break;
      }
      
      //if dealer has blackjack code
      if(dealer.hasBlackjack()) {

        cout << "Dealer got a blackjack!" << endl;
        cout << "Dealer automatically won the round!!" << endl;
        //set round records
        last.winner = dealer.getName();
        last.score = 21;
        lastround = true;
        cout << "Return to main menu to manage game records.. and start a new round!" << endl;
        break;
      }

      //first hit round
      string reply;
      cout << "Hit or Stand?" << endl;
      cin >> reply;

      if (reply == "Hit" || reply == "Stand") {
        if (reply == "Hit") {

          Card card3 = drawcard();
          p1.hit(card3);
          cout << "Card: " << card3.toString() << endl;
          //check if ace
          bool acecard = false;
          for (Card check : p1.getHand()) {
            if (check.getRank() == "Ace") {
              acecard = true;
            }
          }
          if (acecard) {
            cout << "You have an Ace! Your new score is: " << p1.getScore() << endl;
          } else {
            cout << "New Score: " << p1.getScore() << "!" << endl;
          }
        } else if (reply == "Stand") {
          p1.stand();
          cout << "Your score stands at " << p1.getScore() << endl;
        }
      } else {
        cout << "Please enter Hit or Stand." << endl;
      }

      if(dealer.dealerDecision()) {
        Card d3 = drawcard();
        dealer.hit(d3);
      } else {
        dealer.stand();
      }

      //remaing hit or stand
      while(!p1.standing() && !p1.isBusted() && !dealer.isBusted() && p1.getScore() != 21) {
        string reply;
        cout << "Hit or Stand?" << endl;
        cin >> reply;

        if (reply == "Hit" || reply == "Stand") {
          if (reply == "Hit") {
  
            Card cardn = drawcard();
            p1.hit(cardn);
            cout << "Card: " << cardn.toString() << endl;
            //check if ace
            bool acecard = false;
            for (Card check : p1.getHand()) {
              if (check.getRank() == "Ace") {
                acecard = true;
              }
            }
            if (acecard) {
              cout << "You have an Ace! Your new score is: " << p1.getScore() << endl;
            } else {
              cout << "New Score: " << p1.getScore() << "!" << endl;
            }
          } else if (reply == "Stand") {
            p1.stand();
            cout << "Your score stands at " << p1.getScore() << endl;
          }
        } else {
          cout << "Please enter Hit or Stand." << endl;
        }
  
        if(dealer.dealerDecision()) {
          Card dn = drawcard();
          dealer.hit(dn);
        } else {
          dealer.stand();
        }

      } //end of while loop

      //Check if anyone hit 21 (auto win)
      if (p1.getScore() == 21) {
        cout << "YAYY TWENTY ONE!!" << endl;
        cout << "You have automatically won the round!" << endl;
        //set round records
        last.winner = p1.getName();
        last.score = p1.getScore();
        lastround = true;
        cout << "Return to main menu to manage game records.. and start a new round!" << endl;
        break;
      }

      if (dealer.getScore() == 21) {
        cout << "DANG TWENTY ONE!!" << endl;
        cout << "Dealer has automatically won the round!" << endl;
        //set round records
        last.winner = dealer.getName();
        last.score = dealer.getScore();
        lastround = true;
        cout << "Return to main menu to manage game records.. and start a new round!" << endl;
        break;
      }

      //check if anyone bust (auto lost)
      if (p1.isBusted()) {
        cout << p1.getName() << " busted!! Your score exceed 21, Dealer wins round.. :(" << endl;
        last.winner = dealer.getName();
        last.score = dealer.getScore();
        lastround = true;
        cout << "Return to main menu to manage game records.. and start a new round!" << endl;
        break;
      }

      if(dealer.isBusted()) {
        cout << dealer.getName() << " busted!! Score exceed 21, " << p1.getName() << " wins round.. :)" << endl;
        last.winner = p1.getName();
        last.score = p1.getScore();
        lastround = true;
        cout << "Return to main menu to manage game records.. and start a new round!" << endl;
        break;
      }
      
      //check in if everyone is standing 
      if (p1.standing() && dealer.standing()) {
        cout << "Both players are standing, we will now reveal hands to declare a winner!!" << endl;
        cout << p1.getName() << " has hand: " << endl;
        p1.printHand();
        cout << endl;
        cout << dealer.getName() << " has hand: " << endl;
        dealer.printHand();
        cout << endl;

        if(p1.getScore() > dealer.getScore() && p1.getScore() <= 21) {

          cout << "You have won the round!!" << endl;
          //set round records
          last.winner = p1.getName();
          last.score = p1.getScore();
          lastround = true;
          cout << "Return to main menu to manage game records.. and start a new round!" << endl;
          break;
        } else if (p1.getScore() < dealer.getScore() && dealer.getScore() <= 21 ) {

          cout << dealer.getName() << " wins round.. :(" << endl;
          last.winner = dealer.getName();
          last.score = dealer.getScore();
          lastround = true;
          cout << "Return to main menu to manage game records.. and start a new round!" << endl;
          break;
        }
      } 
    } //game play code
    default:
    cout << "Please enter a valid option: " << endl;
    }
  } while (option != 0);
    return 0;
}
