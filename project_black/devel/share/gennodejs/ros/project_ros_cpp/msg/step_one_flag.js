// Auto-generated. Do not edit!

// (in-package project_ros_cpp.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class step_one_flag {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.done_flag = null;
    }
    else {
      if (initObj.hasOwnProperty('done_flag')) {
        this.done_flag = initObj.done_flag
      }
      else {
        this.done_flag = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type step_one_flag
    // Serialize message field [done_flag]
    bufferOffset = _serializer.int32(obj.done_flag, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type step_one_flag
    let len;
    let data = new step_one_flag(null);
    // Deserialize message field [done_flag]
    data.done_flag = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'project_ros_cpp/step_one_flag';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '17baec0563bbecdba8661f601b44ff3e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 done_flag
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new step_one_flag(null);
    if (msg.done_flag !== undefined) {
      resolved.done_flag = msg.done_flag;
    }
    else {
      resolved.done_flag = 0
    }

    return resolved;
    }
};

module.exports = step_one_flag;
