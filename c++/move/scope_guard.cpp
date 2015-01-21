/**
 * ScopeGuard is a general implementation of the "Initialization is
 * Resource Acquisition" idiom.  Basically, it guarantees that a function
 * is executed upon leaving the currrent scope unless otherwise told.
 *
 * The makeGuard() function is used to create a new ScopeGuard object.
 * It can be instantiated with a lambda function, a std::function<void()>,
 * a functor, or a void(*)() function pointer.
 *
 *
 * Usage example: Add a friend to memory iff it is also added to the db.
 */

void User::addFriend(User& newFriend) {
    // add the friend to memory
    friends_.push_back(&newFriend);

    // If the db insertion that follows fails, we should
    // remove it from memory.
    // (You could also declare this as "auto guard = makeGuard(...)")
    ScopeGuard guard = makeGuard([&] { friends_.pop_back(); });

    // this will throw an exception upon error, which
    // makes the ScopeGuard execute UserCont::pop_back()
    // once the Guard's destructor is called.
    db_->addFriend(GetName(), newFriend.GetName());

    // an exception was not thrown, so don't execute
    // the Guard.
    guard.dismiss();
}


