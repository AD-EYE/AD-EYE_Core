from std_msgs.msg import Bool
import os, sys

sys.path.insert(1, os.path.join(sys.path[0], '..'))

import subprocess
import unittest

from manager import ManagerStateMachine


def getStateMachineToEnabled(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initial_checks_callback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.ENABLED_STATE.value:
        raise Exception('State machine could not get in Enabled state to start test, check getStateMachineToEnabled '
                        'function')


def getStateMachineToEngaged(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initial_checks_callback(test_msg)
    manager_state_machine.activation_request_callback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.ENGAGED_STATE.value:
        raise Exception('State machine could not get in Engaged state to start test, check getStateMachineToEngaged '
                        'function')


def getStateMachineToFault(manager_state_machine):
    test_msg = Bool(True)
    manager_state_machine.initial_checks_callback(test_msg)
    manager_state_machine.activation_request_callback(test_msg)
    manager_state_machine.fault_callback(test_msg)
    if manager_state_machine.getState() != manager_state_machine.States.FAULT_STATE.value:
        raise Exception('State machine could not get in Fault state to start test, check getStateMachineToFault '
                        'function')


class ManagerStateMachineTester(unittest.TestCase):

    # Test all transitions from initial state
    def test_initial_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE.value)

    def test_initial_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE.value)

    def test_initial_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE.value)

    def test_initial_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE.value)

    def test_initial_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_initial_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.INITIALIZING_STATE.value)

    # Test all transitions from enabled state
    def test_enabled_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE.value)

    def test_enabled_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE.value)

    def test_enabled_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE.value)

    def test_enabled_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE.value)

    def test_enabled_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_enabled_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEnabled(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE.value)

    # Test all transitions from engaged state
    def test_engaged_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE.value)

    def test_engaged_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE.value)

    def test_engaged_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE.value)

    def test_engaged_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENABLED_STATE.value)

    def test_engaged_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_engaged_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToEngaged(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.ENGAGED_STATE.value)

    # Test all transitions from fault state
    def test_fault_initial_checks_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_fault_initial_checks_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.initial_checks_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_fault_activation_request_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_fault_activation_request_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.activation_request_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_fault_fault_true(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(True)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)

    def test_fault_fault_false(self):
        manager_state_machine = ManagerStateMachine()
        getStateMachineToFault(manager_state_machine)
        test_msg = Bool(False)
        manager_state_machine.fault_callback(test_msg)
        self.assertEqual(manager_state_machine.getState(), manager_state_machine.States.FAULT_STATE.value)


if __name__ == '__main__':
    # subprocess.Popen('roscore')
    unittest.main()
