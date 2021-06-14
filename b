==6548== Memcheck, a memory error detector
==6548== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==6548== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==6548== Command: ./build/bomberman
==6548== 
==6548== Conditional jump or move depends on uninitialised value(s)
==6548==    at 0x541752: RAY::ModelAnimations::ModelAnimations(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x4FD08E: BBM::Runner::createPlayer(WAL::Scene&) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x4C9EF6: BBM::LobbySystem::switchToGame(WAL::Wal&) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x51918A: BBM::Runner::loadLobbyScene()::{lambda(WAL::Entity&, WAL::Wal&)#3}::operator()(WAL::Entity&, WAL::Wal&) const (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x520084: void std::__invoke_impl<void, BBM::Runner::loadLobbyScene()::{lambda(WAL::Entity&, WAL::Wal&)#3}&, WAL::Entity&, WAL::Wal&>(std::__invoke_other, BBM::Runner::loadLobbyScene()::{lambda(WAL::Entity&, WAL::Wal&)#3}&, WAL::Entity&, WAL::Wal&) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x51F0A0: std::enable_if<is_invocable_r_v<void, BBM::Runner::loadLobbyScene()::{lambda(WAL::Entity&, WAL::Wal&)#3}&, WAL::Entity&, WAL::Wal&>, std::enable_if>::type std::__invoke_r<void, BBM::Runner::loadLobbyScene()::{lambda(WAL::Entity&, WAL::Wal&)#3}&, WAL::Entity&, WAL::Wal&>(void&&, (BBM::Runner::loadLobbyScene()::{lambda(WAL::Entity&, WAL::Wal&)#3}&)...) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x51E27A: std::_Function_handler<void (WAL::Entity&, WAL::Wal&), BBM::Runner::loadLobbyScene()::{lambda(WAL::Entity&, WAL::Wal&)#3}>::_M_invoke(std::_Any_data const&, WAL::Entity&, WAL::Wal&) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x4515E6: std::function<void (WAL::Entity&, WAL::Wal&)>::operator()(WAL::Entity&, WAL::Wal&) const (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x451481: WAL::Callback<WAL::Entity&, WAL::Wal&>::operator()(WAL::Entity&, WAL::Wal&) const (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x49A22D: BBM::MenuControllableSystem::_updateCurrentButton(bool, BBM::Vector2<float>) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x49A401: BBM::MenuControllableSystem::onFixedUpdate(WAL::ViewEntity<BBM::ControllableComponent>&) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x49F7A7: WAL::System<BBM::ControllableComponent>::fixedUpdate() (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548== 
==6548== 
==6548== Process terminating with default action of signal 1 (SIGHUP)
==6548==    at 0x494951: WAL::ViewIterator<__gnu_cxx::__normal_iterator<std::tuple<std::reference_wrapper<WAL::Entity>, std::reference_wrapper<BBM::PositionComponent>, std::reference_wrapper<BBM::CollisionComponent> >*, std::vector<std::tuple<std::reference_wrapper<WAL::Entity>, std::reference_wrapper<BBM::PositionComponent>, std::reference_wrapper<BBM::CollisionComponent> >, std::allocator<std::tuple<std::reference_wrapper<WAL::Entity>, std::reference_wrapper<BBM::PositionComponent>, std::reference_wrapper<BBM::CollisionComponent> > > > >, BBM::PositionComponent, BBM::CollisionComponent>::operator++() (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x4944A2: BBM::CollisionSystem::onFixedUpdate(WAL::ViewEntity<BBM::PositionComponent, BBM::CollisionComponent>&) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x49937B: WAL::System<BBM::PositionComponent, BBM::CollisionComponent>::fixedUpdate() (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x41154E: void WAL::Wal::_run<BBM::GameState>(WAL::Callback<WAL::Wal&, BBM::GameState&> const&, BBM::GameState) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x40DA60: void WAL::Wal::run<BBM::GameState>(WAL::Callback<WAL::Wal&, BBM::GameState&> const&, BBM::GameState) (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x40871B: BBM::Runner::run() (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548==    by 0x406F15: main (in /home/arthurjamet/Desktop/B4/YEP/Bomberman/build/bomberman)
==6548== 
==6548== HEAP SUMMARY:
==6548==     in use at exit: 85,100,138 bytes in 63,937 blocks
==6548==   total heap usage: 200,879 allocs, 136,942 frees, 426,519,550 bytes allocated
==6548== 
==6548== LEAK SUMMARY:
==6548==    definitely lost: 408 bytes in 1 blocks
==6548==    indirectly lost: 0 bytes in 0 blocks
==6548==      possibly lost: 6,687,735 bytes in 41,704 blocks
==6548==    still reachable: 78,411,995 bytes in 22,232 blocks
==6548==         suppressed: 0 bytes in 0 blocks
==6548== Rerun with --leak-check=full to see details of leaked memory
==6548== 
==6548== Use --track-origins=yes to see where uninitialised values come from
==6548== For lists of detected and suppressed errors, rerun with: -s
==6548== ERROR SUMMARY: 4383708 errors from 1 contexts (suppressed: 0 from 0)
