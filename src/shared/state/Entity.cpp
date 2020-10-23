
namespace state {

  /// class Entity - 
  class Entity {
    // Attributes
  private:
    static int instanceId;
    int uid;
  protected:
    int attack;
    int defense;
    int income;
    // Operations
  public:
    virtual bool const isEmpty ();
    virtual bool const isTree ();
    virtual bool const isFacility ();
    virtual bool const isSoldier ();
    // Setters and Getters
    int getAttack() const;
    void setAttack(int attack);
    int getDefense() const;
    void setDefense(int defense);
    int getIncome() const;
    void setIncome(int income);
  };

};