// Auto-generated. Do not edit!

// (in-package project_ros_python.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class nano_control {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.move_message = null;
    }
    else {
      if (initObj.hasOwnProperty('move_message')) {
        this.move_message = initObj.move_message
      }
      else {
        this.move_message = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type nano_control
    // Serialize message field [move_message]
    bufferOffset = _serializer.int32(obj.move_message, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type nano_control
    let len;
    let data = new nano_control(null);
    // Deserialize message field [move_message]
    data.move_message = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'project_ros_python/nano_control';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '09377968f5a8b50b28685fd8aea01579';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 move_message
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new nano_control(null);
    if (msg.move_message !== undefined) {
      resolved.move_message = msg.move_message;
    }
    else {
      resolved.move_message = 0
    }

    return resolved;
    }
};

module.exports = nano_control;
