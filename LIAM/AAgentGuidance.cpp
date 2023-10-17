#include <vector>
#include <cmath>
#include <iostream>

class AgentGuidance {
public:
    static std::vector<std::pair<GameObject, bool>> ActiveAgents;
    
    Vector3 a_currentAvoidanceVector = Vector3::zero();
    float a_avoidanceStartTime = 2.0f;
    float a_avoidanceDuration = 1.0f;
    float a_maxTurnSpeed = 50.0f;
    bool a_isActive = true;
    
    enum GuidanceType {
        PROPORTIONALNAVIGATION = 0
    };

    enum TargetType {
        TARGET = 0,
        PATH = 1
    };

    struct GuidanceSettings {
        TargetType a_targetType = TARGET;
        bool a_limitAcceleration = true;
        float a_maxAcceleration = 100.0f;
        GuidanceType a_guidanceType;
        GameObject a_target;
        bool a_loopPath = false;
        float a_tTurnIn = 0.5f;
        float a_turnMarginSimple = 0.0f;
        float a_pathN = 4.0f;
        float a_CLOSN = 4.0f;
        std::vector<GameObject> a_pathObjs;
        float a_N = 4;
        std::vector<Vector3> a_lastObjPos;

        Vector3 GetPathPos(int idx) {
            return a_pathObjs[idx].transform.position;
        }

        Vector3 GetPathPosLoop(int idx) {
            return GetPathPos(idx % PathCount());
        }

        int PathCount() {
            return a_pathObjs.size();
        }

        std::vector<Vector3> GetPathPositions() {
            a_lastObjPos.clear();
            for (auto& o : a_pathObjs) {
                if (o) a_lastObjPos.push_back(o.transform.position);
            }
            return a_lastObjPos;
        }
    };

    GameObject a_agent;
    Rigidbody a_agentRb;
    KinematicEstimator a_targetState;
    Vector3 a_lastCommandUsedForAttitude;
    Vector3 a_currentCommand = Vector3::zero();
    GuidanceSettings a_settings;
    Vector3 a_startPos;
    Vector3 a_startDir;
    Vector3 a_aimPoint;
    IntEvent a_eventNextWayPoint;
    bool a_firstCommand = true;
    float a_lastTime;
    std::vector<Vector3> a_debugPos;
    std::vector<Vector3> a_debugLine;

    AgentGuidance(GameObject agent, GuidanceSettings settings) : a_agent(agent), a_settings(settings) {
        if (!a_agent) std::cerr << "A valid agent object must be provided when instantiating agent guidance" << std::endl;
        
        a_agentRb = a_agent.GetComponent<Rigidbody>();
        if (a_settings.a_target) a_targetState = KinematicEstimator(a_settings.a_target);

        ActiveAgents.push_back(std::make_pair(a_agent, true));
    }

    void AttitudeAdjustment() {
        float dt = (a_firstCommand) ? 0.0f : Time.time - a_lastTime;
        
        if (a_agentRb.velocity.sqrMagnitude < std::numeric_limits<float>::epsilon()) return;
        Vector3 up;
        up = Vector3::up;

        auto oldRot = a_agent.transform.rotation;
        
        Quaternion newRot;
        if (a_firstCommand)
            newRot = oldRot;
        else
            newRot = Quaternion::Lerp(oldRot, Quaternion::LookRotation(a_agentRb.velocity, up), dt / 0.1f);
        
        a_agentRb.MoveRotation(newRot);
    }

    void CommandAgent(bool doControl) {
        auto command = GetCommand();
        
        AttitudeAdjustment();
        if (!doControl) return;

        command = VectorCalculation.LimitMagnitude(command, 1000.0f);
        
        for (const auto& agent : ActiveAgents) {
            if (agent.first != a_agent && agent.second) {
                float distance = Vector3::Distance(a_agent.transform.position, agent.first.transform.position);
                if (distance < 50.0f) {
                    Vector3 avoidanceVector = (a_agent.transform.position - agent.first.transform.position).normalized * a_settings.a_maxAcceleration;
                    a_currentAvoidanceVector = avoidanceVector;
                    a_avoidanceStartTime = Time.time;
                }
            }
        }

        Vector3 newDirection = Vector3::RotateTowards(a_agentRb.velocity.normalized, a_currentAvoidanceVector.normalized, Mathf::Deg2Rad * a_maxTurnSpeed * Time.deltaTime, 0.0f);
        a_agentRb.velocity = newDirection * a_agentRb.velocity.magnitude;
        
        a_agentRb.AddForce(command, ForceMode::Acceleration);
        
        a_currentCommand = command;
        
        a_firstCommand = false;
        a_lastTime = Time.time;
        
        if (Time.time - a_avoidanceStartTime > a_avoidanceDuration) {
            ReacquireTarget();
        }
    }

    void ReacquireTarget() {
        a_targetState = KinematicEstimator(a_settings.a_target);
    }

    virtual Vector3 GetCommand() = 0;

    virtual bool AimingForTarget() {
        return true;
    }

    void GetTargetState(Vector3& pos, Vector3& vel) {
        if (a_targetState != nullptr) {
            pos = a_targetState.GetPos();
            vel = a_targetState.GetVel();
        } else {
            pos = Vector3::zero();
            vel = Vector3::zero();
        }
    }
};
