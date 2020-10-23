
namespace state {

  /// class Territory - 
  class Territory {
    // Attributes
  private:
    static int instanceCount;
    int uid;
    int[2] capitalCoords;
    int savings;
    int income;
    int wages;
    int balance;
     size;
    // Operations
  public:
    Territory ();
    ~Territory ();
    Territory* const clone ();
    // Setters and Getters
  };

};