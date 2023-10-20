using System.Collections.Generic;
using UnityEngine;

namespace SparseDesign
{
    namespace ControlledFlight
    {
        abstract public class AgentGuidance
        {
            public static List<(GameObject, bool)> ActiveAgents = new List<(GameObject, bool)>();

            private Vector3 a_currentAvoidanceVector = Vector3.zero;
            private float a_avoidanceStartTime = 2f;
            private float a_avoidanceDuration = 1.0f; 
            private float a_maxTurnSpeed = 50f; 

            protected bool a_isActive = true; 

            public static AgentGuidance GetNewInstance(GameObject agent, GuidanceSettings settings)
            {
                AgentGuidance guidance;

                if (settings.a_targetType == AgentGuidance.TargetType.TARGET)
                {
                    switch (settings.a_guidanceType)
                    {
                        case GuidanceType.PROPORTIONALNAVIGATION:
                            guidance = new ProportionalNavigation(agent: agent, settings: settings);
                            break;
                        default:
                            Debug.LogError($"Missing handling of guidance type {settings.a_guidanceType}");
                            guidance = new ProportionalNavigation(agent: agent, settings: settings);
                            break;
                    }
                }
                else if (settings.a_targetType == TargetType.PATH)
                {
                    guidance = new PathFollow(agent: agent, settings: settings);
                }
                else
                {
                    Debug.LogError($"Missing handling of guidance type {settings.a_guidanceType}");
                    guidance = new ProportionalNavigation(agent, settings);
                }

                return guidance;
            }

            public enum GuidanceType
            {
                PROPORTIONALNAVIGATION = 0,
            }

            public enum TargetType
            {
                TARGET = 0,
                PATH = 1
            }

            [System.Serializable]
            public class GuidanceSettings
            {
                public TargetType a_targetType = TargetType.TARGET;
                public bool a_limitAcceleration = true;
                public float a_maxAcceleration = 100;
                public GuidanceType a_guidanceType = default;
                public GameObject a_target = default;
                public bool a_loopPath = false;
                [Range(0.01f, 10)] public float a_tTurnIn = 0.5f;
                [Range(-1, 1)] public float a_turnMarginSimple = 0f;
                [Range(2, 20)] public float a_pathN = 4f;
                [Range(2, 20)] public float a_CLOSN = 4f;
                public List<GameObject> a_pathObjs = new List<GameObject>();
                [Range(2, 20)] public float a_N = 4;
                public Vector3 GetPathPos(int idx)
                {
                    return a_pathObjs[idx].transform.position;
                }

                public Vector3 GetPathPosLoop(int idx)
                {
                    return GetPathPos(idx % this.PathCount());
                }

                public int PathCount()
                {
                    return a_pathObjs.Count;
                }

                private List<Vector3> a_lastObjPos = new List<Vector3>();

                public List<Vector3> GetPathPositions()
                {
                    a_lastObjPos.Clear();
                    foreach (var o in a_pathObjs)
                    {
                        if (o) a_lastObjPos.Add(o.transform.position);
                    }
                    return a_lastObjPos;
                }
            }

            public GameObject a_agent = default;
            protected Rigidbody a_agentRb = default;
            protected KinematicEstimator a_targetState;
            protected Vector3 a_lastCommandUsedForAttitude = default;
            public Vector3 a_currentCommand { private set; get; } = Vector3.zero;
            [SerializeField] public GuidanceSettings a_settings = new GuidanceSettings();

            public Vector3 a_startPos { protected set; get; } = default;
            public Vector3 a_startDir { protected set; get; } = default;
            public Vector3 a_aimPoint { protected set; get; } = default;
            public IntEvent a_eventNextWayPoint = new IntEvent();
            private bool a_firstCommand = true;
            private float a_lastTime = default;
            public List<Vector3> a_debugPos { protected set; get; } = new List<Vector3>();
            public List<Vector3> a_debugLine { protected set; get; } = new List<Vector3>();

            public AgentGuidance(GameObject agent, GuidanceSettings settings)
            {
                if (!agent) Debug.LogError("A valid agent object must be provided when instantiating agent guidance");
                a_agent = agent;

                if (settings == null) Debug.LogError("Valid settings must be provided when instantiating agent guidance");

                a_settings = settings;

                a_agentRb = a_agent.GetComponent<Rigidbody>();
                if (a_settings.a_target) a_targetState = new KinematicEstimator(a_settings.a_target);

                ActiveAgents.Add((a_agent, true)); 
            }

            public void AttitudeAdjustment()
            {
                float dt = (a_firstCommand) ? 0f : Time.time - a_lastTime;

                if (a_agentRb.velocity.sqrMagnitude < float.Epsilon) return;
                Vector3 up;
                up = Vector3.up;

                var oldRot = a_agent.transform.rotation;

                Quaternion newRot;
                if (a_firstCommand)
                    newRot = oldRot;
                else
                    newRot = Quaternion.Lerp(oldRot, Quaternion.LookRotation(a_agentRb.velocity, up), dt / 0.1f);

                a_agentRb.MoveRotation(newRot);
            }

            public void CommandAgent(bool doControl)
            {
                var command = GetCommand();

                AttitudeAdjustment();
                if (!doControl) return;

                command = VectorCalculation.LimitMagnitude(command, 1000f);

                foreach (var (otherAgent, isActive) in ActiveAgents)
                {
                    if (otherAgent != a_agent && isActive)
                    {
                        
                        float distance = Vector3.Distance(a_agent.transform.position, otherAgent.transform.position);
                        if (distance < 50f)
                        {
                            Vector3 avoidanceVector = (a_agent.transform.position - otherAgent.transform.position).normalized * a_settings.a_maxAcceleration;
                            a_currentAvoidanceVector = avoidanceVector;
                            a_avoidanceStartTime = Time.time;
                        }
                    }
                }

                
                Vector3 newDirection = Vector3.RotateTowards(a_agentRb.velocity.normalized, a_currentAvoidanceVector.normalized, Mathf.Deg2Rad * a_maxTurnSpeed * Time.deltaTime, 0.0f);
                a_agentRb.velocity = newDirection * a_agentRb.velocity.magnitude;

                a_agentRb.AddForce(command, ForceMode.Acceleration);

                a_currentCommand = command;

                a_firstCommand = false;
                a_lastTime = Time.time;

                
                if (Time.time - a_avoidanceStartTime > a_avoidanceDuration)
                {
                    
                    ReacquireTarget();
                }
            }

            private void ReacquireTarget()
            {
                a_targetState = new KinematicEstimator(a_settings.a_target);
            }

            abstract protected Vector3 GetCommand();

            virtual public bool AimingForTarget()
            {
                return true;
            }

            virtual public void GetTargetState(out Vector3 pos, out Vector3 vel)
            {
                if (a_targetState != null)
                {
                    pos = a_targetState.GetPos();
                    vel = a_targetState.GetVel();
                }
                else
                {
                    pos = Vector3.zero;
                    vel = Vector3.zero;
                }
            }
        }
    }
}
