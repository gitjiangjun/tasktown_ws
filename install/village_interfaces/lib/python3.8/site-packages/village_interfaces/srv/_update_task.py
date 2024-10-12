# generated from rosidl_generator_py/resource/_idl.py.em
# with input from village_interfaces:srv/UpdateTask.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'tasks'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_UpdateTask_Request(type):
    """Metaclass of message 'UpdateTask_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('village_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'village_interfaces.srv.UpdateTask_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__update_task__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__update_task__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__update_task__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__update_task__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__update_task__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class UpdateTask_Request(metaclass=Metaclass_UpdateTask_Request):
    """Message class 'UpdateTask_Request'."""

    __slots__ = [
        '_tasks',
    ]

    _fields_and_field_types = {
        'tasks': 'sequence<int32>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.tasks = array.array('i', kwargs.get('tasks', []))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.tasks != other.tasks:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def tasks(self):
        """Message field 'tasks'."""
        return self._tasks

    @tasks.setter
    def tasks(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'i', \
                "The 'tasks' array.array() must have the type code of 'i'"
            self._tasks = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'tasks' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._tasks = array.array('i', value)


# Import statements for member types

# Member 'tasks_result'
# already imported above
# import array

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_UpdateTask_Response(type):
    """Metaclass of message 'UpdateTask_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('village_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'village_interfaces.srv.UpdateTask_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__update_task__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__update_task__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__update_task__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__update_task__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__update_task__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class UpdateTask_Response(metaclass=Metaclass_UpdateTask_Response):
    """Message class 'UpdateTask_Response'."""

    __slots__ = [
        '_tasks_result',
    ]

    _fields_and_field_types = {
        'tasks_result': 'sequence<int32>',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('int32')),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.tasks_result = array.array('i', kwargs.get('tasks_result', []))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.tasks_result != other.tasks_result:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def tasks_result(self):
        """Message field 'tasks_result'."""
        return self._tasks_result

    @tasks_result.setter
    def tasks_result(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'i', \
                "The 'tasks_result' array.array() must have the type code of 'i'"
            self._tasks_result = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -2147483648 and val < 2147483648 for val in value)), \
                "The 'tasks_result' field must be a set or sequence and each value of type 'int' and each integer in [-2147483648, 2147483647]"
        self._tasks_result = array.array('i', value)


class Metaclass_UpdateTask(type):
    """Metaclass of service 'UpdateTask'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('village_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'village_interfaces.srv.UpdateTask')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__update_task

            from village_interfaces.srv import _update_task
            if _update_task.Metaclass_UpdateTask_Request._TYPE_SUPPORT is None:
                _update_task.Metaclass_UpdateTask_Request.__import_type_support__()
            if _update_task.Metaclass_UpdateTask_Response._TYPE_SUPPORT is None:
                _update_task.Metaclass_UpdateTask_Response.__import_type_support__()


class UpdateTask(metaclass=Metaclass_UpdateTask):
    from village_interfaces.srv._update_task import UpdateTask_Request as Request
    from village_interfaces.srv._update_task import UpdateTask_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
