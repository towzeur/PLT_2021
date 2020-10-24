
namespace state {

  /// class Territory - 
  class Territory {
    // Attributes
  private:
    static int instanceCount;
    int uid;
    int capitalCoords[2];
    int savings;
    int income;
    int wages;
    int balance;
    int size;
    // Operations
  public:
    Territory ();
    ~Territory ();
    Territory* const clone ();
    // Setters and Getters
  };

};